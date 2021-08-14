#include <powell_function.h>

namespace powell {

struct F1 {
    template <typename T>
    bool operator()(const T* const x1, const T* const x2, T* residual) const {
        residual[0] = x1[0] + 10.0 * x2[0];
        return true;
    }
};

struct F2 {
    template <typename T>
    bool operator()(const T* const x3, const T* const x4, T* residual) const {
        residual[0] = sqrt(5) * (x3[0] - x4[0]);
        return true;
    }
};

struct F3 {
    template <typename T>
    bool operator()(const T* const x2, const T* const x3, T* residual) const {
        residual[0] = (x2[0] - 2.0 * x3[0]) * (x2[0] - 2.0 * x3[0]);
        return true;
    }
};

struct F4 {
    template <typename T>
    bool operator()(const T* const x1, const T* const x4, T* residual) const {
        residual[0] = sqrt(10.0) * (x1[0] - x4[0]) * (x1[0] - x4[0]);
        return true;
    }
};

void solve() {
    // Define the initial values
    double x1 = 3.0;
    double x2 = -1.0;
    double x3 = 0.0;
    double x4 = 1.0;

    // Declare the problem
    ceres::Problem problem;

    // Add residual terms to the problem using the autodiff
    // wrapper to get the derivates automatically
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<F1, 1, 1, 1>(new F1), nullptr, &x1,
        &x2);
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<F2, 1, 1, 1>(new F2), nullptr, &x3,
        &x4);
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<F3, 1, 1, 1>(new F3), nullptr, &x2,
        &x3);
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<F4, 1, 1, 1>(new F4), nullptr, &x1,
        &x4);

    // Run the solver
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout << summary.BriefReport() << "\n";
}

}  // namespace powell