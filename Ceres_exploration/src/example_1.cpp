#include <example_1.h>

namespace example_one {
struct CostFunctor {
    template <typename T>
    bool operator()(const T* const x, T* residual) const {
        residual[0] = 10.0 - x[0];
        return true;
    }
};

void solve() {
    // The variable to solve for with its initial value
    double initial_x = 5.0;
    double x = initial_x;

    // Build the problem
    ceres::Problem problem;

    // Set up the only cost function (also know as residual). This uses
    // auto-differentiation to obtain the derivative (Jacobian)
    ceres::CostFunction* cost_function =
        new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
    problem.AddResidualBlock(cost_function, nullptr, &x);

    // Run the solver
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout << summary.BriefReport() << "\n";
    std::cout << "x : " << initial_x << " -> " << x << "\n";
}

}  // namespace example_one
