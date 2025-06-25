#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <string>
#include <numeric>
#include <iomanip>
#include <direct.h> // For _mkdir

// Matrix type definition
using Matrix = std::vector<std::vector<double>>;

// Function declarations
// QuickSort
template <typename T>
int partition(std::vector<T>& arr, int low, int high);

template <typename T>
void quicksort(std::vector<T>& arr, int low, int high);

template <typename T>
void quicksort(std::vector<T>& arr);

std::vector<int> generate_random_array(int size, int min_val = 1, int max_val = 1000);

// Fibonacci
unsigned long long fibonacci(int n);

// Matrix Multiplication
Matrix matrix_multiplication_standard(const Matrix& A, const Matrix& B);
Matrix generate_random_matrix(int n);

// Ensure results directory exists
void ensure_results_dir() {
    _mkdir("../results");
}

// Save results to CSV file
void save_results_to_csv(const std::vector<std::pair<int, double>>& results, 
                         const std::string& filename) {
    ensure_results_dir();
    std::ofstream file("../results/" + filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    
    file << "Input Size,Execution Time (seconds)\n";
    for (const auto& result : results) {
        file << result.first << "," << result.second << "\n";
    }
    
    file.close();
    std::cout << "Results saved to ../results/" << filename << std::endl;
}

// QuickSort implementation
template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quicksort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

template <typename T>
void quicksort(std::vector<T>& arr) {
    if (arr.size() <= 1) return;
    quicksort(arr, 0, arr.size() - 1);
}

// Generate random array
std::vector<int> generate_random_array(int size, int min_val, int max_val) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min_val, max_val);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

// Recursive Fibonacci implementation
unsigned long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Standard matrix multiplication
Matrix matrix_multiplication_standard(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<double>(n, 0.0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}

// Generate a random matrix
Matrix generate_random_matrix(int n) {
    Matrix matrix(n, std::vector<double>(n));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    
    return matrix;
}

// Benchmark QuickSort with multiple runs
std::vector<std::pair<int, double>> run_quicksort_benchmark(const std::vector<int>& sizes, int num_runs = 5) {
    std::vector<std::pair<int, double>> results;
    std::cout << "\nRunning QuickSort Benchmark..." << std::endl;
    
    for (int size : sizes) {
        std::cout << "Testing array size " << size << "..." << std::endl;
        
        // Generate random array once to use in all runs
        std::vector<int> arr = generate_random_array(size);
        std::vector<double> run_times;
        
        for (int run = 0; run < num_runs; ++run) {
            // Measure execution time
            auto start = std::chrono::high_resolution_clock::now();
            
            std::vector<int> arr_copy = arr; // Create a copy to sort
            quicksort(arr_copy);
            
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            
            run_times.push_back(duration.count());
            std::cout << "  Run " << run + 1 << ": " 
                      << std::fixed << std::setprecision(6) << duration.count() << " seconds" << std::endl;
        }
        
        // Calculate average
        double avg_time = std::accumulate(run_times.begin(), run_times.end(), 0.0) / num_runs;
        results.push_back({size, avg_time});
        std::cout << "QuickSort with array size " << size << ": Average " 
                  << std::fixed << std::setprecision(6) << avg_time << " seconds over " << num_runs << " runs" << std::endl;
    }
    
    return results;
}

// Benchmark Fibonacci with multiple runs
std::vector<std::pair<int, double>> run_fibonacci_benchmark(const std::vector<int>& sizes, int num_runs = 5) {
    std::vector<std::pair<int, double>> results;
    std::cout << "\nRunning Fibonacci Benchmark..." << std::endl;
    
    for (int n : sizes) {
        std::cout << "Testing Fibonacci(" << n << ")..." << std::endl;
        std::vector<double> run_times;
        
        for (int run = 0; run < num_runs; ++run) {
            // Measure execution time
            auto start = std::chrono::high_resolution_clock::now();
            
            fibonacci(n);
            
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            
            run_times.push_back(duration.count());
            std::cout << "  Run " << run + 1 << ": " 
                      << std::fixed << std::setprecision(6) << duration.count() << " seconds" << std::endl;
        }
        
        // Calculate average
        double avg_time = std::accumulate(run_times.begin(), run_times.end(), 0.0) / num_runs;
        results.push_back({n, avg_time});
        std::cout << "Fibonacci(" << n << "): Average " 
                  << std::fixed << std::setprecision(6) << avg_time << " seconds over " << num_runs << " runs" << std::endl;
    }
    
    return results;
}

// Benchmark matrix multiplication with multiple runs
std::vector<std::pair<int, double>> run_matrix_multiplication_benchmark(const std::vector<int>& sizes, int num_runs = 5) {
    std::vector<std::pair<int, double>> results;
    std::cout << "\nRunning Matrix Multiplication Benchmark..." << std::endl;
    
    for (int n : sizes) {
        std::cout << "Testing Matrix Size " << n << "x" << n << "..." << std::endl;
        std::vector<double> run_times;
        
        for (int run = 0; run < num_runs; ++run) {
            // Generate random matrices
            Matrix A = generate_random_matrix(n);
            Matrix B = generate_random_matrix(n);
            
            // Measure execution time
            auto start = std::chrono::high_resolution_clock::now();
            
            Matrix C = matrix_multiplication_standard(A, B);
            
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            
            run_times.push_back(duration.count());
            std::cout << "  Run " << run + 1 << ": " 
                      << std::fixed << std::setprecision(6) << duration.count() << " seconds" << std::endl;
        }
        
        // Calculate average
        double avg_time = std::accumulate(run_times.begin(), run_times.end(), 0.0) / num_runs;
        results.push_back({n, avg_time});
        std::cout << "Matrix multiplication " << n << "x" << n << ": Average " 
                  << std::fixed << std::setprecision(6) << avg_time << " seconds over " << num_runs << " runs" << std::endl;
    }
    
    return results;
}

int main() {
    // Define input sizes
    std::vector<int> quicksort_sizes = {1000, 100000, 1000000};
    std::vector<int> fibonacci_sizes = {20, 30, 40};
    std::vector<int> matrix_mult_sizes = {100, 300, 500};
    
    const int num_runs = 5; // Number of runs for each test
    
    // Run benchmarks
    auto qs_results = run_quicksort_benchmark(quicksort_sizes, num_runs);
    auto fib_results = run_fibonacci_benchmark(fibonacci_sizes, num_runs);
    auto mm_results = run_matrix_multiplication_benchmark(matrix_mult_sizes, num_runs);
    
    // Save results
    save_results_to_csv(qs_results, "cpp_quicksort_results.csv");
    save_results_to_csv(fib_results, "cpp_fibonacci_results.csv");
    save_results_to_csv(mm_results, "cpp_matrix_mult_results.csv");
    
    std::cout << "\nAll benchmarks completed successfully." << std::endl;
    
    return 0;
} 