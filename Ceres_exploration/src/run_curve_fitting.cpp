#include <curve_fitting.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    // Generate data for x and y values
    std::vector<double> x_data{0.0, 1.0, 3.0, 2.5, 4.5, 8.7, 9.0};
    std::vector<double> y_data{0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1};

    curve_fitting::solve(x_data, y_data);
    return 0;
}