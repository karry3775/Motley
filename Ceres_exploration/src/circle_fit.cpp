#include <circle_fit.h>

namespace circle_fit {

CircleFitCostFunction::CircleFitCostFunction(double x, double y) : x(x), y(y) {}

ceres::CostFunction* CircleFitCostFunction::create(double x, double y) {
    return (new ceres::AutoDiffCostFunction<CircleFitCostFunction, 1, 1, 1, 1>(
        new CircleFitCostFunction(x, y)));
}

void generateData(std::vector<double>& x_data, std::vector<double>& y_data,
                  double radius, double cx, double cy, double noise_perc,
                  double theta_resolution) {
    CHECK_LE(noise_perc, 1.0);
    CHECK_GE(noise_perc, 0.0);
    CHECK_LE(theta_resolution, 2 * M_PI);
    CHECK_GE(theta_resolution, -2 * M_PI);
    CHECK_NE(theta_resolution, 0.0);

    // Simulate the data using the equation
    // x = r * cos(theta) + cx;
    // y = t * sin(theta) + cy;
    // from theta ranging from 0 to pi

    double theta = 0;
    while (theta < 2 * M_PI) {
        double x = radius * cos(theta) + cx;
        double y = radius * sin(theta) + cy;

        double x_noise = noise_perc * ((((double)rand()) / RAND_MAX) * 2) - 1;
        double y_noise = noise_perc * ((((double)rand()) / RAND_MAX) * 2) - 1;

        x_data.push_back(x);
        y_data.push_back(y);

        theta += theta_resolution;
    }
}

void solve(const std::vector<double>& x_data, const std::vector<double>& y_data,
           double& cx, double& cy, double& radius) {
    CHECK_EQ(x_data.size(), y_data.size());
    // Declare the problem
    ceres::Problem problem;

    // Store the initial values
    double cx0 = cx;
    double cy0 = cy;
    double radius0 = radius;

    double m = sqrt(radius);

    // Add residuals for each data point
    for (size_t i = 0; i < x_data.size(); ++i) {
        // create a cost function for the current data point
        ceres::CostFunction* cost_function =
            CircleFitCostFunction::create(x_data[i], y_data[i]);
        // Add residual
        problem.AddResidualBlock(cost_function, new ceres::HuberLoss(0.1), &cx,
                                 &cy, &m);
    }

    // Set options
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;

    // Create a summary object
    ceres::Solver::Summary summary;

    // Finally solve
    ceres::Solve(options, &problem, &summary);

    // Lets print the final report
    std::cerr << summary.FullReport() << "\n";
    std::cerr << "Initial values --> cx: " << cx0 << ", cy: " << cy0
              << ", radius: " << radius0 << "\n";
    std::cerr << "Initial values --> cx: " << cx << ", cy: " << cy
              << ", radius: " << m * m << "\n";
}

}  // namespace circle_fit