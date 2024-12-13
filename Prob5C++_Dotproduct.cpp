#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

int main() {
int n = 10000;
std::vector<double> a(n), b(n);

for (int i = 0; i<n; i++) {
a[i] = static_cast<double>(rand()) / RAND_MAX;
b[i] = static_cast<double>(rand()) / RAND_MAX;
}


double c = 6.0;
auto start_loop = std::chrono: :high_resolution_clock: :now();
for (int i = @; i<n; i++) {
c += afi] * b[i];

auto end_loop = std::chrono: :high_resolution_clock: :now();
std::chrono::duration<double> timeloop = end_loop - start_loop;

auto start_vec = std::chrono::high_resolution_clock: :now();
double cc = 0.0;
for (int i = @; i <n; i++) {

cc += afi] * b[i];
}
auto end_vec = std::chrono::high_resolution_clock: :now();
std::chrono::duration<double> timevec = end_vec - start_vec;


std::cout << "Dot Product (loop): " << c << std::endl;

std::cout << "Dot Product (vectorized): " << cc << std::endl;

std::cout << "Difference between results: " << std::fabs(c - cc) << std::endl;


double speedup = timeloop.count() / timevec.count();

std::cout << "Time taken by loop: " << timeloop.count() << " seconds" << std::endl;
std::cout << “Time taken by vectorization: " << timevec.count() << " seconds” << std::endl;
std::cout << "Speedup: " << speedup << std::endl;

return 0;

}
