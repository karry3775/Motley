#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>

int main() {
    // Number 1:
    // Lesson in not mixing data types
    // Gotcha --> .cast<double> instead of .cast<double>()
    Eigen::Matrix<float, 2, 3> matrix_23;
    Eigen::Vector3d v_3d(1, 2, 3);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cerr << matrix_23(i, j) << "\t";
        }
        std::cerr << "\n";
    }

    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;

    std::cerr << result << "\n";

    // Number 2:
    // Basic matrix operations
    Eigen::Matrix3d m_3d = Eigen::Matrix3d::Random();  // Random number matrix
    std::cerr << "random matrix: \n" << m_3d << "\n";
    std::cerr << "transpose: \n" << m_3d.transpose() << "\n";
    std::cerr << "sum: \n" << m_3d.sum() << "\n";
    std::cerr << "trace: \n" << m_3d.trace() << "\n";
    std::cerr << "times 10: \n" << 10 * m_3d << "\n";
    std::cerr << "inverse: \n" << m_3d.inverse() << "\n";
    std::cerr << "det: \n" << m_3d.determinant() << "\n";

    // Number 3:
    // Eigen Values
    // Real symmetric matrix can guarantee successful diagonalization
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(
        m_3d.transpose() * m_3d);
    std::cerr << "Eigen value = \n" << eigen_solver.eigenvalues() << "\n";
    std::cerr << "Eigen vectors = \n" << eigen_solver.eigenvectors() << "\n";

    // Number 4: (Advantages of QR and cholesky become more apparent
    // for bigger size matrices)
    // ALSO For now we do not know, how to work around:
    // OBJECT_ALLOCATED_ON_STACK_IS_TOO_BIG (Cannot do 1000+ for now \_(;)_/)
    // Solving equations
    // We solve the equation of matrix_NN * x = v_Nd
    //                       (N X N) * (N x 1) = (N x 1)
    constexpr int kMatrixSize = 100;
    Eigen::Matrix<double, kMatrixSize, kMatrixSize> m_NN =
        Eigen::MatrixXd::Random(kMatrixSize, kMatrixSize);

    // Make the matrix semi-positive definite
    m_NN = m_NN * m_NN.transpose();

    // Get a vector
    Eigen::Matrix<double, kMatrixSize, 1> v_Nd =
        Eigen::MatrixXd::Random(kMatrixSize, 1);

    clock_t time_start = clock();  // timing

    // Direction inversion (takes more time)
    Eigen::Matrix<double, kMatrixSize, 1> x = m_NN.inverse() * v_Nd;

    std::cerr << "time of normal inverse is: "
              << 1000 * (clock() - time_start) /
                     static_cast<double>(CLOCKS_PER_SEC)
              << "ms\n";
    std::cerr << "x = " << x.transpose() << "\n";

    // In practice generally solved by matrix decomposition, such as QR,
    // the speed will be much faster (Doesn't seem like much for smaller
    // matrices)
    time_start = clock();
    x = m_NN.colPivHouseholderQr().solve(v_Nd);
    std::cerr << "time of QR decomposition is: "
              << 1000 * (clock() - time_start) /
                     static_cast<double>(CLOCKS_PER_SEC)
              << "ms\n";
    std::cerr << "x = " << x.transpose() << "\n";

    // For positive definite matrices, you can also use cholesky decomposition
    // to solve equations
    time_start = clock();
    x = m_NN.ldlt().solve(v_Nd);
    std::cerr << "time of ldlt decomposition is: "
              << 1000 * (clock() - time_start) /
                     static_cast<double>(CLOCKS_PER_SEC)
              << "ms\n";

    std::cerr << "x = " << x.transpose() << "\n";

    return 0;
}