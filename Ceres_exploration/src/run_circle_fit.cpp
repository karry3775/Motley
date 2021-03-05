#include <circle_fit.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    // Generate points of a circle, to act as data
    std::vector<double> x_data{}, y_data{};
    circle_fit::generateData(x_data, y_data, 3, 1, 1, 0.0, M_PI / 180);

    // Print out the data
    std::cerr << "Data values are : \n";
    for (size_t i = 0; i < x_data.size(); ++i) {
        std::cerr << x_data[i] << ", " << y_data[i] << "\n";
    }
    std::cerr << "=======================================\n";

    double cx{0.0}, cy{0.0}, r{0.0};
    circle_fit::solve(x_data, y_data, cx, cy, r);

    return 0;
}