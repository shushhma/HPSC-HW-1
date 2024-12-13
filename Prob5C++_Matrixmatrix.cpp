#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

double calculateNorm(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B, int n) {
    double norm = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            norm += (A[i][j] - B[i][j]) * (A[i][j] - B[i][j]);
        }
    }
    return std::sqrt(norm);
}

int main() {
    const int n = 1000;  
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<std::vector<double>> B(n, std::vector<double>(n));
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));   
    std::vector<std::vector<double>> CC(n, std::vector<double>(n, 0.0)); 
    std::vector<std::vector<double>> CCC(n, std::vector<double>(n, 0.0)); 

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = static_cast<double>(rand()) / RAND_MAX;
            B[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeloop = end - start;
    std::cout << "Time for loop-based computation: " << timeloop.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                CC[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeloopvec = end - start;
    std::cout << "Time for partial vectorized computation: " << timeloopvec.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            CCC[i][j] = 0.0;
            for (int k = 0; k < n; ++k) {
                CCC[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timevec = end - start;
    std::cout << "Time for fully vectorized computation: " << timevec.count() << " seconds\n";

    double norm1 = calculateNorm(C, CC, n);
    double norm2 = calculateNorm(C, CCC, n);
    std::cout << "Norm between C and CC: " << norm1 << "\n";
    std::cout << "Norm between C and CCC: " << norm2 << "\n";

    double speedup = timeloop.count() / timeloopvec.count();
    double speedup2 = timeloop.count() / timevec.count();
    double speedup3 = timeloopvec.count() / timevec.count();

    std::cout << "Speedup of loop-based vs partial vectorization: " << speedup << "\n";
    std::cout << "Speedup of loop-based vs full vectorization: " << speedup2 << "\n";
    std::cout << "Speedup of partial vectorization vs full vectorization: " << speedup3 << "\n";

    return 0;
}

