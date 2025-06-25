# Algorithm Performance Comparison: Python vs C++

This project provides a performance comparison between Python and C++ implementations of three common algorithms:
1. QuickSort
2. Fibonacci (recursive)
3. Matrix Multiplication

## Project Structure

```
Algo/
├── cpp/                   # C++ implementations
│   ├── quicksort.cpp
│   ├── fibonacci.cpp
│   ├── matrix_mult.cpp
│   ├── benchmark.cpp      # Runs all C++ benchmarks
│   └── Makefile
├── python/                # Python implementations
│   ├── quicksort.py
│   ├── fibonacci.py
│   ├── matrix_mult.py
│   └── benchmark.py       # Runs all Python benchmarks
├── results/               # CSV files with benchmark results
└── visualization/
    └── plot_results.py    # Creates comparison visualizations
```

## Requirements

### Python
- Python 3.6+
- NumPy
- Matplotlib

### C++
- C++17 compatible compiler (e.g., GCC 8+ or MSVC 19.14+)
- Standard Library

## Setup Instructions

### Python Setup
```bash
pip install numpy matplotlib
```

### C++ Setup
On Windows with MinGW:
```bash
cd cpp
g++ -std=c++17 -o benchmark benchmark.cpp -lstdc++fs
```

On Linux/macOS:
```bash
cd cpp
make
```

## Running the Benchmarks

### Python Benchmarks
```bash
cd python
python benchmark.py
```

This will run all Python benchmarks and save the results in CSV format to the `results` directory.

You can also run individual algorithm benchmarks:
```bash
python quicksort.py
python fibonacci.py
python matrix_mult.py
```

### C++ Benchmarks
```bash
cd cpp
./benchmark     # Unix/Linux/macOS
benchmark.exe   # Windows
```

Or run individual algorithm benchmarks:
```bash
./quicksort     # Unix/Linux/macOS
quicksort.exe   # Windows
```

## Visualizing Results

After running both Python and C++ benchmarks, generate visualizations with:
```bash
cd visualization
python plot_results.py
```

This will create comparison charts in the `results` directory.

## Algorithm Details

### 1. QuickSort
- Implementation: Standard recursive quicksort
- Input sizes: 1,000 (small), 100,000 (medium), 1,000,000 (large)
- Metric: Execution time in seconds

### 2. Fibonacci (Recursive)
- Implementation: Pure recursive calculation
- Input sizes: 20 (small), 30 (medium), 40 (large)
- Metric: Execution time in seconds

### 3. Matrix Multiplication
- Implementation: Standard O(n³) algorithm
- Matrix sizes: 100×100 (small), 300×300 (medium), 500×500 (large)
- Python also includes NumPy implementation for comparison
- Metric: Execution time in seconds

## Expected Results

You should observe that:
1. C++ generally outperforms Python for CPU-bound tasks
2. The performance gap increases with input size
3. For matrix operations, Python with NumPy (which uses optimized C code) may be competitive with or even outperform the naive C++ implementation
4. Recursive Fibonacci demonstrates exponential time growth in both languages

## Extending the Project

To add new algorithms:
1. Create implementation files in both `python/` and `cpp/` directories
2. Add benchmark functions to the benchmark scripts
3. Update the visualization script to include the new algorithm 