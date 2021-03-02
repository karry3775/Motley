#include <robot_pose_mle.h>

DEFINE_double(corridor_length, 30.0,
              "Length of the corridor that the robot is travelling down.");

DEFINE_double(
    pose_separation, 0.5,
    "The distance that the robot traverse between successive odometry updates");

DEFINE_double(odometry_stddev, 0.1,
              "The standard deviation of odometry error of the robot.");

DEFINE_double(range_stddev, 0.01,
              "The standard deviation of range readings of the robot.");

namespace robot_pose_mle {

// The stride length of the dynamic_autodiff_cost_function evaluator
static constexpr int kStride = 10;

struct OdometryConstraint {
    // Creating a typdef
    typedef ceres::AutoDiffCostFunction<OdometryConstraint,
                                        /** size of the reidual block **/ 1,
                                        /** size of the parameter block*/ 1>
        OdometryCostFunction;

    // Constructor
    OdometryConstraint(double odometry_mean, double odometry_stddev)
        : odometry_mean(odometry_mean), odometry_stddev(odometry_stddev) {}

    // Functor
    template <typename T>
    bool operator()(const T* const odometry, T* residual) const {
        // Maybe the incoming odometry is the one we are optimizing
        // and it just checks with calculated/ predicted odometry
        residual[0] = (odometry[0] - odometry_mean) / odometry_stddev;
        return true;
    }

    // There seems to be a running trend to make a create function
    // to hide the creation of the AutoDiff
    static OdometryCostFunction* Create(const double odometry_value) {
        return new OdometryCostFunction(
            new OdometryConstraint(odometry_value, FLAGS_odometry_stddev));
    }

   private:
    const double odometry_mean;
    const double odometry_stddev;
};

struct RangeConstraint {
    // Create a typdef for cost function
    typedef ceres::DynamicAutoDiffCostFunction<RangeConstraint, kStride>
        RangeCostFunction;

    // Constructor
    RangeConstraint(int pose_index, double range_reading, double range_stddev,
                    double corridor_length)
        : pose_index(pose_index),
          range_reading(range_reading),
          range_stddev(range_stddev),
          corridor_length(corridor_length) {}

    template <typename T>
    bool operator()(T const* const* relative_poses, T* residual) const {
        // Teamplated global pose to be calculated via aggregating relative
        // poses
        T global_pose(0.0);  // Initialize with 0

        // Aggregate
        // NOTE: Since this a pointer type array, we cannot explcitly
        // find out the number of poses, by just doing .size()
        // which highlights the importance of the pose_index data member
        for (int i = 0; i <= pose_index; ++i) {
            global_pose += relative_poses[i][0];
        }

        residual[0] =
            (global_pose + range_reading - corridor_length) / range_stddev;

        return true;
    }

    // Factory method to create the cost function
    static RangeCostFunction* Create(const int pose_index,
                                     const double range_reading,
                                     std::vector<double>* odometry_values,
                                     std::vector<double*>* parameter_blocks) {
        RangeConstraint* constraint =
            new RangeConstraint(pose_index, range_reading, FLAGS_range_stddev,
                                FLAGS_corridor_length);
        RangeCostFunction* cost_function = new RangeCostFunction(constraint);

        // Add all paarameter block that affect this constraint
        parameter_blocks->clear();

        for (int i = 0; i <= pose_index; ++i) {
            parameter_blocks->push_back(&((*odometry_values)[i]));
            cost_function->AddParameterBlock(1);
        }

        cost_function->SetNumResiduals(1);
        return (cost_function);
    }

   private:
    const int pose_index;
    const double range_reading;
    const double range_stddev;
    const double corridor_length;
};

void simulateRobot(std::vector<double>* odometry_values,
                   std::vector<double>* range_readings) {
    const int num_steps =
        static_cast<int>(ceil(FLAGS_corridor_length / FLAGS_pose_separation));

    // The robot starts out at the origin
    double robot_location = 0.0;

    // Perturb the range and odometry readings from the ground
    // truth i.e. deterministic case
    for (int i = 0; i < num_steps; ++i) {
        const double actual_odometry_value = std::min(
            FLAGS_pose_separation, FLAGS_corridor_length - robot_location);

        robot_location += actual_odometry_value;

        // NOTE: How the range is calculated after the pose is updated
        const double actual_range = FLAGS_corridor_length - robot_location;

        const double observed_odometry =
            RandNormal() * FLAGS_odometry_stddev + actual_odometry_value;

        const double observed_range =
            RandNormal() * FLAGS_range_stddev + actual_range;

        odometry_values->push_back(observed_odometry);
        range_readings->push_back(observed_range);
    }
}

void printState(const std::vector<double>& odometry_readings,
                const std::vector<double>& range_readings) {
    CHECK_EQ(odometry_readings.size(), range_readings.size());

    double robot_location = 0.0;
    std::cerr << "Pose: location  odom  range  r.error  o.error\n";
    for (int i = 0; i < odometry_readings.size(); ++i) {
        robot_location += odometry_readings[i];
        const double range_error =
            robot_location + range_readings[i] - FLAGS_corridor_length;

        const double odometry_error =
            FLAGS_pose_separation - odometry_readings[i];

        std::cerr << static_cast<int>(i) << "  " << robot_location << "  "
                  << odometry_readings[i] << "  " << range_readings[i] << "  "
                  << range_error << "  " << odometry_error << "\n";
    }
}

void solve(std::vector<double>& odometry_values,
           const std::vector<double>& range_readings) {
    // Declare the problem
    ceres::Problem problem;

    for (int i = 0; i < odometry_values.size(); ++i) {
        // Create and add a DynamicAutoDiffCostFUnction for the RangeConstraint
        // from pose i
        std::vector<double*> parameter_blocks;
        RangeConstraint::RangeCostFunction* range_cost_function =
            RangeConstraint::Create(i, range_readings[i], &odometry_values,
                                    &parameter_blocks);
        problem.AddResidualBlock(range_cost_function, nullptr,
                                 parameter_blocks);

        // Create and add an AutoDiffCostFUnction for the OdometryContraint
        // for pose i
        problem.AddResidualBlock(OdometryConstraint::Create(odometry_values[i]),
                                 nullptr, &(odometry_values[i]));
    }

    // Solvin' time
    ceres::Solver::Options solver_options;
    solver_options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;
    ceres::Solve(solver_options, &problem, &summary);

    std::cerr << summary.FullReport() << "\n";
    LOG(INFO) << "Final values";
    printState(odometry_values, range_readings);
}

}  // namespace robot_pose_mle