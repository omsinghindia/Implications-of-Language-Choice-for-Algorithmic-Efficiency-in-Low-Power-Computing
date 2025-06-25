import time
import os
import csv
import matplotlib.pyplot as plt
from quicksort import quicksort, generate_random_array
from fibonacci import fibonacci
from matrix_mult import matrix_multiplication_standard, matrix_multiplication_numpy, generate_random_matrix, generate_random_matrix_numpy

def ensure_results_dir():
    """Ensure the results directory exists"""
    if not os.path.exists("../results"):
        os.makedirs("../results")

def run_quicksort_benchmark(sizes=[100, 1000, 10000], num_runs=5):
    """Run QuickSort benchmark with multiple runs and average the results"""
    results = []
    print("\nRunning QuickSort Benchmark...")
    
    for size in sizes:
        total_time = 0
        print(f"Testing array size {size}...")
        
        # Generate random array once to use in all runs
        arr = generate_random_array(size)
        
        for run in range(num_runs):
            # Measure execution time
            start_time = time.time()
            quicksort(arr.copy())
            execution_time = time.time() - start_time
            
            print(f"  Run {run+1}: {execution_time:.6f} seconds")
            total_time += execution_time
            
        # Calculate average
        avg_time = total_time / num_runs
        results.append((size, avg_time))
        print(f"QuickSort with array size {size}: Average {avg_time:.6f} seconds over {num_runs} runs")
    
    return results

def run_fibonacci_benchmark(sizes=[10, 20, 30], num_runs=5):
    """Run Fibonacci benchmark with multiple runs and average the results"""
    results = []
    print("\nRunning Fibonacci Benchmark...")
    
    for n in sizes:
        total_time = 0
        print(f"Testing Fibonacci({n})...")
        
        for run in range(num_runs):
            # Measure execution time
            start_time = time.time()
            fibonacci(n)
            execution_time = time.time() - start_time
            
            print(f"  Run {run+1}: {execution_time:.6f} seconds")
            total_time += execution_time
            
        # Calculate average
        avg_time = total_time / num_runs
        results.append((n, avg_time))
        print(f"Fibonacci({n}): Average {avg_time:.6f} seconds over {num_runs} runs")
    
    return results

def run_matrix_multiplication_benchmark(sizes=[10, 50, 100], num_runs=5):
    """Run Matrix Multiplication benchmark with multiple runs and average the results"""
    results_standard = []
    results_numpy = []
    print("\nRunning Matrix Multiplication Benchmark...")
    
    for n in sizes:
        total_time_standard = 0
        total_time_numpy = 0
        print(f"Testing Matrix Size {n}x{n}...")
        
        for run in range(num_runs):
            # Standard implementation
            A = generate_random_matrix(n)
            B = generate_random_matrix(n)
            
            start_time = time.time()
            matrix_multiplication_standard(A, B)
            execution_time_standard = time.time() - start_time
            
            print(f"  Run {run+1} Standard: {execution_time_standard:.6f} seconds")
            total_time_standard += execution_time_standard
            
            # NumPy implementation
            A_np = generate_random_matrix_numpy(n)
            B_np = generate_random_matrix_numpy(n)
            
            start_time = time.time()
            matrix_multiplication_numpy(A_np, B_np)
            execution_time_numpy = time.time() - start_time
            
            print(f"  Run {run+1} NumPy: {execution_time_numpy:.6f} seconds")
            total_time_numpy += execution_time_numpy
        
        # Calculate averages
        avg_time_standard = total_time_standard / num_runs
        avg_time_numpy = total_time_numpy / num_runs
        
        results_standard.append((n, avg_time_standard))
        print(f"Standard matrix multiplication {n}x{n}: Average {avg_time_standard:.6f} seconds over {num_runs} runs")
        
        results_numpy.append((n, avg_time_numpy))
        print(f"NumPy matrix multiplication {n}x{n}: Average {avg_time_numpy:.6f} seconds over {num_runs} runs")
    
    return results_standard, results_numpy

def save_results_to_csv(results, filename):
    """Save benchmark results to CSV file"""
    ensure_results_dir()
    with open(f"../results/{filename}", 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Input Size', 'Execution Time (seconds)'])
        for size, time in results:
            writer.writerow([size, time])
    print(f"Results saved to ../results/{filename}")

def benchmark_all(num_runs=5):
    """Run all benchmarks and save results"""
    # Define input sizes
    quicksort_sizes = [1000, 100000, 1000000]
    fibonacci_sizes = [20, 30, 40]
    matrix_mult_sizes = [100, 300, 500]
    
    # Run benchmarks
    qs_results = run_quicksort_benchmark(quicksort_sizes, num_runs)
    fib_results = run_fibonacci_benchmark(fibonacci_sizes, num_runs)
    mm_results_standard, mm_results_numpy = run_matrix_multiplication_benchmark(matrix_mult_sizes, num_runs)
    
    # Save results
    save_results_to_csv(qs_results, 'python_quicksort_results.csv')
    save_results_to_csv(fib_results, 'python_fibonacci_results.csv')
    save_results_to_csv(mm_results_standard, 'python_matrix_mult_standard_results.csv')
    save_results_to_csv(mm_results_numpy, 'python_matrix_mult_numpy_results.csv')
    
    return {
        'quicksort': qs_results,
        'fibonacci': fib_results,
        'matrix_standard': mm_results_standard,
        'matrix_numpy': mm_results_numpy
    }

if __name__ == "__main__":
    benchmark_all(5)  # Run 5 times for each test 