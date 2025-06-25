# Algorithm Performance Results

This directory contains the benchmark results and visualizations comparing the performance of Python and C++ implementations of various algorithms.

## CSV Files

After running the benchmarks, the following CSV files will be generated:

### Python Results
- `python_quicksort_results.csv`: QuickSort performance in Python
- `python_fibonacci_results.csv`: Recursive Fibonacci performance in Python
- `python_matrix_mult_standard_results.csv`: Standard matrix multiplication in Python
- `python_matrix_mult_numpy_results.csv`: NumPy-optimized matrix multiplication in Python

### C++ Results
- `cpp_quicksort_results.csv`: QuickSort performance in C++
- `cpp_fibonacci_results.csv`: Recursive Fibonacci performance in C++
- `cpp_matrix_mult_results.csv`: Matrix multiplication performance in C++

## CSV Format

Each CSV file contains two columns:
1. `Input Size`: The size of the input (array size for QuickSort, n for Fibonacci, matrix dimension for matrix multiplication)
2. `Execution Time (seconds)`: The time taken to execute the algorithm

## Visualizations

After running the visualization script, the following PNG files will be generated:

- `quicksort_comparison.png`: Comparison of Python vs C++ QuickSort performance
- `fibonacci_comparison.png`: Comparison of Python vs C++ recursive Fibonacci performance
- `matrix_multiplication_comparison.png`: Comparison of matrix multiplication performance (Python standard, Python NumPy, C++)
- `all_algorithms_comparison.png`: Summary chart showing all algorithm comparisons

## Analyzing Results

When analyzing the results, consider the following:

1. **Relative Performance**: How much faster is C++ compared to Python for each algorithm?
2. **Scaling Behavior**: How does the performance gap change as the input size increases?
3. **Algorithm Complexity**: Do the results match the theoretical time complexity of the algorithms?
4. **NumPy vs. Native Code**: For matrix multiplication, compare the performance of Python's NumPy (which uses optimized C code) against the native C++ implementation.

## Extending Analysis

To add more analysis:

1. Add new benchmarks to the Python and C++ benchmark scripts
2. Update the visualization script to create additional charts
3. Compare different algorithm implementations or optimizations 