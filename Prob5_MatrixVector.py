import numpy as np
import time

n = 300
A = np.random.rand(n, n)
B = np.random.rand(n, n)
C = np.zeros((n, n))
CC = np.zeros((n, n))

start = time.perf_counter()
for i in range(n):
    for j in range(n):
        for k in range(n):
            C[i, j] += A[i, k] * B[k, j]
timeloop = time.perf_counter() - start
print(f"Time for loop-based computation: {timeloop:.6f} seconds")

start = time.perf_counter()
for j in range(n):
    CC[:, j] = np.dot(A, B[:, j])
timeloopvec = time.perf_counter() - start
print(f"Time for partial vectorized computation: {timeloopvec:.6f} seconds")

start = time.perf_counter()
CCC = np.dot(A, B)
timevec = time.perf_counter() - start
print(f"Time for fully vectorized computation: {timevec:.6f} seconds")

norm1 = np.linalg.norm(C - CC)
norm2 = np.linalg.norm(C - CCC)
print(f"Norm between C and CC: {norm1:.6f}")
print(f"Norm between C and CCC: {norm2:.6f}")

speedup = timeloop / timeloopvec if timeloopvec > 0 else float('inf')
speedup2 = timeloop / timevec if timevec > 0 else float('inf')
speedup3 = timeloopvec / timevec if timevec > 0 else float('inf')

print(f"Speedup of loop-based vs partial vectorization: {speedup:.2f}")
print(f"Speedup of loop-based vs full vectorization: {speedup2:.2f}")
print(f"Speedup of partial vectorization vs full vectorization: {speedup3:.2f}")
