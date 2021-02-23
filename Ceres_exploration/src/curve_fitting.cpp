#include <curve_fitting.h>

namespace curve_fitting {

struct ExponentialResidual {
    // Constructor
    ExponentialResidual(double x, double y) : x_{x}, y_{y} {}

    template <typename T>
    bool operator()(const T* const m, const T* const c, T* residual) const {
        residual[0] = y_ - exp(m[0] * x_ + c[0]);
        return true;
    }

   private:
    double x_;
    double y_;
};

void solve(const std::vector<double>& x_data,
           const std::vector<double>& y_data) {
    // Define initial values for m and c
    double m = 0.0;
    double c = 0.0;

    // Declare the problem
    ceres::Problem problem;

    // For each element of the data add a cost function
    // and the task of ceres should be to minimize the residual
    // by finding optimal m and c [Note this would not do
    // outlier rejection -- which is common to any least squares
    // problem]
    CHECK(x_data.size() == y_data.size())
        << " Sizes do not match for x and y data vectors " << x_data.size()
        << " vs " << y_data.size();

    // The only steps in populating a problem
    // seems to be
    // 1. Create a cost function with some sort of
    // differentiation technique (auto, numerical, analytical)
    // 2. Use that cost function and add it as a residual block

    for (size_t i = 0; i < x_data.size(); ++i) {
        // Defining a cost function for every x and y value
        ceres::CostFunction* cost_function =
            new ceres::AutoDiffCostFunction<ExponentialResidual, 1, 1, 1>(
                new ExponentialResidual(x_data[i], y_data[i]));
        problem.AddResidualBlock(cost_function, nullptr, &m, &c);
    }

    // Now we need to solve the problem
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;

    // summar
    ceres::Solver::Summary summary;

    // Actual solving
    ceres::Solve(options, &problem, &summary);

    // spit out the brief report
    std::cout << summary.BriefReport() << "\n";

    // TODO check the final values of m and c
    std::cout << "Initial m: " << 0.0 << " c:" << 0.0 << "\n";
    std::cout << "Final m: " << m << " c: " << c << std::endl;
}

}  // namespace curve_fitting