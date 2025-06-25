import time
import random
import numpy as np

def matrix_multiplication_standard(A, B):
    """
    Standard implementation of matrix multiplication
    """
    n = len(A)
    C = [[0 for _ in range(n)] for _ in range(n)]
    
    for i in range(n):
        for j in range(n):
            for k in range(n):
                C[i][j] += A[i][k] * B[k][j]
    
    return C

def matrix_multiplication_numpy(A, B):
    """
    NumPy implementation of matrix multiplication
    """
    return np.dot(A, B)

def generate_random_matrix(n):
    """
    Generate a random n x n matrix
    """
    return [[random.random() for _ in range(n)] for _ in range(n)]

def generate_random_matrix_numpy(n):
    """
    Generate a random n x n matrix using NumPy
    """
    return np.random.rand(n, n)

def benchmark_matrix_multiplication(sizes=[10, 50, 100]):
    """
    Benchmark matrix multiplication with different matrix sizes
    """
    results_standard = []
    results_numpy = []
    
    for n in sizes:
        # Standard implementation
        A = generate_random_matrix(n)
        B = generate_random_matrix(n)
        
        start_time = time.time()
        matrix_multiplication_standard(A, B)
        execution_time_standard = time.time() - start_time
        
        results_standard.append((n, execution_time_standard))
        print(f"Standard matrix multiplication {n}x{n}: {execution_time_standard:.6f} seconds")
        
        # NumPy implementation
        A_np = generate_random_matrix_numpy(n)
        B_np = generate_random_matrix_numpy(n)
        
        start_time = time.time()
        matrix_multiplication_numpy(A_np, B_np)
        execution_time_numpy = time.time() - start_time
        
        results_numpy.append((n, execution_time_numpy))
        print(f"NumPy matrix multiplication {n}x{n}: {execution_time_numpy:.6f} seconds")
    
    return results_standard, results_numpy

if __name__ == "__main__":
    # Example usage
    benchmark_matrix_multiplication([100, 300, 500]) 