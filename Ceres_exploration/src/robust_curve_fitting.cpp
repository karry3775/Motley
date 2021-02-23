#include <robust_curve_fitting.h>

namespace robust_curve_fitting {

struct ExponentialResidual {
    ExponentialResidual(double x, double y) : x_{x}, y_{y} {}

    // Now a templated evaluator needs to defined
    template <typename T>
    bool operator()(const T* const m, const T* const c, T* residual) const {
        // y - e^(mx + c)
        residual[0] = y_ - exp(m[0] * x_ + c[0]);
        return true;
    }

   private:
    double x_;
    double y_;
};

void solve(const std::vector<double>& x_data,
           const std::vector<double>& y_data) {
    CHECK(x_data.size() == y_data.size())
        << "Sizes do not match for x and y data " << x_data.size() << " vs "
        << y_data.size();

    // First step is to define some initial values for m and c
    double m = 0.0;
    double c = 0.0;

    // Declare the problem
    ceres::Problem problem;

    // Now we need to add each residual separately by iterating over the block
    for (size_t i = 0; i < x_data.size(); ++i) {
        // Create a cost function and add it as a residual
        ceres::CostFunction* cost_function =
            new ceres::AutoDiffCostFunction<ExponentialResidual, 1, 1, 1>(
                new ExponentialResidual(x_data[i], y_data[i]));

        problem.AddResidualBlock(
            cost_function,
            /** instead of nullptr using CauchyLoss to reject outliers*/
            new ceres::CauchyLoss(0.5), &m, &c);
    }

    // Now we begin to solve the problem that has been defined above
    // Step 1: Define the options and the summary object
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;

    // Finally solve
    ceres::Solve(options, &problem, &summary);

    // Finally print out the brief report
    std::cout << summary.BriefReport() << "\n";
    std::cout << "Initial m: " << 0.0 << " c: " << 0.0 << "\n";
    std::cout << "Final m: " << m << " c: " << c << "\n";
}

}  // namespace robust_curve_fitting
