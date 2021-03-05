#include "bundle_adjustment.h"
#include "ceres/rotation.h"

namespace bundle_adjustment {

class BalProblemReader {
   public:
    ~BalProblemReader() {
        // For destroying all the pointer objects
        // Can be later switched to smart pointers
        delete[] point_index_;
        delete[] camera_index_;
        delete[] observations_;
        delete[] parameters_;
    }

    int numObservations() const { return num_observations_; }

    const double* observations() const { return observations_; }

    double* mutableCameras() { return parameters_; }

    double* mutablePoints() { return parameters_ + 9 * num_cameras_; }

    double* mutableCameraForObservation(int i) {
        return mutableCameras() + camera_index_[i] * 9;
    }

    double* mutablePointForObservation(int i) {
        return mutablePoints() + point_index_[i] * 3;
    }

    bool loadFile(const char* filename) {
        FILE* fptr = fopen(filename, "r");
        if (fptr == NULL) return false;

        FscanfOrDie(fptr, "%d", &num_cameras_);
        FscanfOrDie(fptr, "%d", &num_points_);
        FscanfOrDie(fptr, "%d", &num_observations_);

        point_index_ = new int[num_observations_];
        camera_index_ = new int[num_observations_];
        observations_ = new double[2 * num_observations_];

        // Since each camera has 9 params and each point has 3
        num_parameters_ = 9 * num_cameras_ + 3 * num_points_;
        parameters_ = new double[num_parameters_];

        for (int i = 0; i < num_observations_; ++i) {
            FscanfOrDie(fptr, "%d", camera_index_ + i);
            FscanfOrDie(fptr, "%d", point_index_ + i);
            for (int j = 0; j < 2; ++j) {
                FscanfOrDie(fptr, "%lf", observations_ + 2 * i + j);
            }
        }

        for (int i = 0; i < num_parameters_; ++i) {
            FscanfOrDie(fptr, "%lf", parameters_ + i);
        }

        return true;
    }

   private:
    template <typename T>
    void FscanfOrDie(FILE* fptr, const char* format, T* value) {
        int num_scanned = fscanf(fptr, format, value);
        if (num_scanned != 1) {
            LOG(FATAL) << "Invalid UW data file. Num scanned: " << num_scanned;
        }
    }

    int num_cameras_;
    int num_points_;
    int num_observations_;
    int num_parameters_;

    int* point_index_;
    int* camera_index_;
    double* observations_;
    double* parameters_;
};

/**
 * Template pinhole camera model to be used with Ceres. The camera is
 * parameterized using 9 parameters: 3 for rotation, 3 for translation, 1 for
 * focal length, 2 for radial distortion. The principal point is not
 * modeled (i,e it is assumed to be located at the image center)
 */
struct SnavelyReprojectionError {
    SnavelyReprojectionError(double observed_x, double observed_y)
        : observed_x{observed_x}, observed_y{observed_y} {}

    // Can also refer to here for what formula to use:
    // source : http://grail.cs.washington.edu/projects/bal/
    template <typename T>
    bool operator()(const T* const camera, const T* const point,
                    T* residuals) const {
        // Aim for this method is to basically transform the 3D point
        // which is in world frame back to the image pixel coordinate
        // which basically turns out to be K[R | T] kinda transformation

        // So lets first apply the rotation
        // Camera [0, 1, 2] are the angle-axis rotation
        T p[3];
        ceres::AngleAxisRotatePoint(camera, point, p);

        // Now lets apply the translation
        // camera[3, 4, 5] are the translation components
        p[0] += camera[3];
        p[1] += camera[4];
        p[2] += camera[5];

        // At this stage we are done with [R |T] transformation
        // Now we need to correct for camera intrinsics which will also
        // include the distortional correction in addition to the focal length
        // scaling

        // To that effect, compute the center of distortion. The sign change
        // comes from teh camera model that Noah Snavely's Bundler assumes,
        // whereby the camera coordinate system has a negative z axis

        // This step has basically converted it to homogenous coordinates
        // without the focal length and radial distortion correction
        // This step is also called  (perspective division)
        T xp = -p[0] / p[2];
        T yp = -p[1] / p[2];

        // Apply second and fourth order radial distortion
        const T& l1 = camera[7];
        const T& l2 = camera[8];
        T r2 = xp * xp + yp * yp;
        T distortion = 1.0 + r2 * (l1 + l2 * r2);

        // Compute the final project point position
        const T& focal = camera[6];
        T predicted_x = focal * distortion * xp;
        T predicted_y = focal * distortion * yp;

        // Finally we can compute the reprojection error and hence
        // our residual
        residuals[0] = predicted_x - observed_x;
        residuals[1] = predicted_y - observed_y;

        return true;
    }

    // Factory to hide the construction of the costfunction object from the
    // client node
    static ceres::CostFunction* Create(const double observed_x,
                                       const double observed_y) {
        return (
            new ceres::AutoDiffCostFunction<SnavelyReprojectionError, 2, 9, 3>(
                new SnavelyReprojectionError(observed_x, observed_y)));
    }

    // These represent the observed pixel coordinates
    double observed_x;
    double observed_y;
};

void solve(char** argv) {
    BalProblemReader bal_problem_reader;

    if (!bal_problem_reader.loadFile(argv[1])) {
        LOG(FATAL) << "Unable to open file " << argv[1];
        return;
    }

    // Extraction observations from bal_problem_reader
    const double* observations = bal_problem_reader.observations();

    // Create residuals for each observation in the bundle adjustment problem.
    // The para meters for cameras and points are added automatically
    ceres::Problem problem;

    for (int i = 0; i < bal_problem_reader.numObservations(); ++i) {
        // Each residual block takes a point and a camera as input and outputs
        // a 2 dimensional residual. Internally, the cost function stores the
        // observeed image location and compares the reprojection against the
        // observation

        ceres::CostFunction* cost_function = SnavelyReprojectionError::Create(
            observations[2 * i + 0], observations[2 * i + 1]);

        problem.AddResidualBlock(
            cost_function, nullptr,
            bal_problem_reader.mutableCameraForObservation(i),
            bal_problem_reader.mutablePointForObservation(i));
    }

    // Make Ceres automatically detect the bundle structure. Note that the
    // standard solver, SPARSE_NORMAL_CHOLESKY, also works fine but it is slower
    // for standard bundle adjustment problems
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_SCHUR;
    options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout << summary.FullReport() << "\n";
}

}  // namespace bundle_adjustment