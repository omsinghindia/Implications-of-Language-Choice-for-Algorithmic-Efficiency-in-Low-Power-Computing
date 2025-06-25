#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

// Matrix type definition
using Matrix = std::vector<std::vector<double>>;

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

// Benchmark matrix multiplication
std::vector<std::pair<int, double>> benchmark_matrix_multiplication(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    
    for (int n : sizes) {
        // Generate random matrices
        Matrix A = generate_random_matrix(n);
        Matrix B = generate_random_matrix(n);
        
        // Measure execution time
        auto start = std::chrono::high_resolution_clock::now();
        
        Matrix C = matrix_multiplication_standard(A, B);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        
        results.push_back({n, duration.count()});
        std::cout << "Matrix multiplication " << n << "x" << n << ": " 
                  << duration.count() << " seconds" << std::endl;
    }
    
    return results;
}

// Save results to CSV file
void save_results_to_csv(const std::vector<std::pair<int, double>>& results, 
                         const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    
    file << "Input Size,Execution Time (seconds)\n";
    for (const auto& result : results) {
        file << result.first << "," << result.second << "\n";
    }
    
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}

int main() {
    std::vector<int> sizes = {100, 300, 500};
    
    std::cout << "Running Matrix Multiplication benchmark..." << std::endl;
    auto results = benchmark_matrix_multiplication(sizes);
    
    // Save results
    save_results_to_csv(results, "../results/cpp_matrix_mult_results.csv");
    
    return 0;
} 