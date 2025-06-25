import os
import csv
import matplotlib.pyplot as plt
import numpy as np

def ensure_results_dir():
    """Ensure the results directory exists"""
    if not os.path.exists("../results"):
        os.makedirs("../results")

def load_csv_results(filename):
    """Load benchmark results from CSV file"""
    results = []
    try:
        with open(f"../results/{filename}", 'r') as csvfile:
            reader = csv.reader(csvfile)
            next(reader)  # Skip header
            for row in reader:
                input_size = int(row[0])
                execution_time = float(row[1])
                results.append((input_size, execution_time))
        return results
    except FileNotFoundError:
        print(f"File ../results/{filename} not found.")
        return []

def plot_algorithm_comparison(python_results, cpp_results, algorithm_name, save_path=None):
    """Plot comparison between Python and C++ implementations of an algorithm"""
    if not python_results or not cpp_results:
        print(f"Not enough data to plot comparison for {algorithm_name}")
        return
    
    # Extract data
    python_sizes = [r[0] for r in python_results]
    python_times = [r[1] for r in python_results]
    cpp_sizes = [r[0] for r in cpp_results]
    cpp_times = [r[1] for r in cpp_results]
    
    # Create plot
    plt.figure(figsize=(10, 6))
    plt.plot(python_sizes, python_times, 'o-', label='Python')
    plt.plot(cpp_sizes, cpp_times, 's-', label='C++')
    plt.title(f'{algorithm_name} - Python vs C++ Performance')
    plt.xlabel('Input Size')
    plt.ylabel('Execution Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.xscale('log')
    
    # Save plot if path provided
    if save_path:
        plt.savefig(save_path)
        print(f"Plot saved to {save_path}")
    
    plt.close()

def plot_all_algorithms(use_log_scale=True):
    """Plot performance comparison for all algorithms"""
    ensure_results_dir()
    
    # Load Python results
    py_quicksort = load_csv_results('python_quicksort_results.csv')
    py_fibonacci = load_csv_results('python_fibonacci_results.csv')
    py_matrix_std = load_csv_results('python_matrix_mult_standard_results.csv')
    py_matrix_numpy = load_csv_results('python_matrix_mult_numpy_results.csv')
    
    # Load C++ results (these will be created later)
    cpp_quicksort = load_csv_results('cpp_quicksort_results.csv')
    cpp_fibonacci = load_csv_results('cpp_fibonacci_results.csv')
    cpp_matrix = load_csv_results('cpp_matrix_mult_results.csv')
    
    # Plot comparisons
    if py_quicksort:
        plt.figure(figsize=(10, 6))
        plt.plot([r[0] for r in py_quicksort], [r[1] for r in py_quicksort], 'o-', label='Python')
        if cpp_quicksort:
            plt.plot([r[0] for r in cpp_quicksort], [r[1] for r in cpp_quicksort], 's-', label='C++')
        plt.title('QuickSort - Performance Comparison')
        plt.xlabel('Array Size')
        plt.ylabel('Execution Time (seconds)')
        plt.legend()
        plt.grid(True)
        if use_log_scale:
            plt.xscale('log')
        plt.savefig('../results/quicksort_comparison.png')
        plt.close()
    
    if py_fibonacci:
        plt.figure(figsize=(10, 6))
        plt.plot([r[0] for r in py_fibonacci], [r[1] for r in py_fibonacci], 'o-', label='Python')
        if cpp_fibonacci:
            plt.plot([r[0] for r in cpp_fibonacci], [r[1] for r in cpp_fibonacci], 's-', label='C++')
        plt.title('Fibonacci - Performance Comparison')
        plt.xlabel('n')
        plt.ylabel('Execution Time (seconds)')
        plt.legend()
        plt.grid(True)
        plt.savefig('../results/fibonacci_comparison.png')
        plt.close()
    
    if py_matrix_std:
        plt.figure(figsize=(10, 6))
        plt.plot([r[0] for r in py_matrix_std], [r[1] for r in py_matrix_std], 'o-', label='Python (Standard)')
        if py_matrix_numpy:
            plt.plot([r[0] for r in py_matrix_numpy], [r[1] for r in py_matrix_numpy], '^-', label='Python (NumPy)')
        if cpp_matrix:
            plt.plot([r[0] for r in cpp_matrix], [r[1] for r in cpp_matrix], 's-', label='C++')
        plt.title('Matrix Multiplication - Performance Comparison')
        plt.xlabel('Matrix Size (n x n)')
        plt.ylabel('Execution Time (seconds)')
        plt.legend()
        plt.grid(True)
        if use_log_scale and max([r[0] for r in py_matrix_std]) > 100:
            plt.xscale('log')
            plt.yscale('log')
        plt.savefig('../results/matrix_multiplication_comparison.png')
        plt.close()
    
    # Create a summary plot with all algorithms
    plt.figure(figsize=(12, 8))
    
    # QuickSort
    if py_quicksort:
        plt.subplot(3, 1, 1)
        plt.title('QuickSort Performance')
        plt.plot([r[0] for r in py_quicksort], [r[1] for r in py_quicksort], 'o-', label='Python')
        if cpp_quicksort:
            plt.plot([r[0] for r in cpp_quicksort], [r[1] for r in cpp_quicksort], 's-', label='C++')
        plt.xlabel('Array Size')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid(True)
        if use_log_scale:
            plt.xscale('log')
    
    # Fibonacci
    if py_fibonacci:
        plt.subplot(3, 1, 2)
        plt.title('Fibonacci Performance')
        plt.plot([r[0] for r in py_fibonacci], [r[1] for r in py_fibonacci], 'o-', label='Python')
        if cpp_fibonacci:
            plt.plot([r[0] for r in cpp_fibonacci], [r[1] for r in cpp_fibonacci], 's-', label='C++')
        plt.xlabel('n')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid(True)
    
    # Matrix Multiplication
    if py_matrix_std:
        plt.subplot(3, 1, 3)
        plt.title('Matrix Multiplication Performance')
        plt.plot([r[0] for r in py_matrix_std], [r[1] for r in py_matrix_std], 'o-', label='Python (Standard)')
        if py_matrix_numpy:
            plt.plot([r[0] for r in py_matrix_numpy], [r[1] for r in py_matrix_numpy], '^-', label='Python (NumPy)')
        if cpp_matrix:
            plt.plot([r[0] for r in cpp_matrix], [r[1] for r in cpp_matrix], 's-', label='C++')
        plt.xlabel('Matrix Size')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid(True)
        if use_log_scale:
            plt.xscale('log')
            plt.yscale('log')
    
    plt.tight_layout()
    plt.savefig('../results/all_algorithms_comparison.png')
    plt.close()

if __name__ == "__main__":
    plot_all_algorithms() 