#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

int main() {
    const int n = 100;  // Size of the matrix and vector
    std::vector<std::vector<double>> A(n, std::vector<double>(n));  // Matrix A
    std::vector<double> x(n);  // Vector x
    std::vector<double> b(n, 0.0);  // Result of loop-based multiplication
    std::vector<double> bb(n, 0.0);  // Result of partial vectorized multiplication
    std::vector<double> bbb(n, 0.0);  // Result of fully vectorized multiplication

    for (int i = 0; i < n; ++i) {
        x[i] = static_cast<double>(rand()) / RAND_MAX;
        for (int j = 0; j < n; ++j) {
            A[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            b[i] += A[i][j] * x[j];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeloop = end - start;
    std::cout << "Time for loop-based computation: " << timeloop.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bb[i] += A[i][j] * x[j];  // This effectively mimics partial vectorization
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeloopvec = end - start;
    std::cout << "Time for partial vectorized computation: " << timeloopvec.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        bbb[i] = 0.0;
        for (int j = 0; j < n; ++j) {
            bbb[i] += A[i][j] * x[j];
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timevec = end - start;
    std::cout << "Time for fully vectorized computation: " << timevec.count() << " seconds\n";

    double norm1 = 0.0, norm2 = 0.0;
    for (int i = 0; i < n; ++i) {
        norm1 += (b[i] - bb[i]) * (b[i] - bb[i]);
        norm2 += (b[i] - bbb[i]) * (b[i] - bbb[i]);
    }
    norm1 = std::sqrt(norm1);
    norm2 = std::sqrt(norm2);
    
    std::cout << "Norm between b and bb: " << norm1 << "\n";
    std::cout << "Norm between b and bbb: " << norm2 << "\n";

    double speedup = timeloop.count() / timeloopvec.count();
    double speedup2 = timeloop.count() / timevec.count();
    double speedup3 = timeloopvec.count() / timevec.count();

    std::cout << "Speedup of loop-based vs partial vectorization: " << speedup << "\n";
    std::cout << "Speedup of loop-based vs full vectorization: " << speedup2 << "\n";
    std::cout << "Speedup of partial vectorization vs full vectorization: " << speedup3 << "\n";

    return 0;
}
