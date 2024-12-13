import numpy as np
import time

# Define the size of the vectors
n = 10000

# Generate two random vectors of size n
a = np.random.rand(n)
b = np.random.rand(n)

# Dot product using a loop
c = 0
start_loop = time.time()
for i in range(n):
    c += a[i] * b[i]
time_loop = time.time() - start_loop

# Dot product using NumPy's vectorized dot function
start_vec = time.time()
cc = np.dot(a, b)
time_vec = time.time() - start_vec

# Print results and compare the performance
print(f"Dot Product (loop): {c}")
print(f"Dot Product (vectorized): {cc}")
print(f"Difference between results: {abs(c - cc)}")

# Calculate and print the speedup
speedup = time_loop / time_vec
print(f"Time taken by loop: {time_loop:.6f} seconds")
print(f"Time taken by vectorization: {time_vec:.6f} seconds")
print(f"Speedup: {speedup:.2f}")
