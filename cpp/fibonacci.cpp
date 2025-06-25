#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

// Recursive Fibonacci implementation
unsigned long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Benchmark Fibonacci
std::vector<std::pair<int, double>> benchmark_fibonacci(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    
    for (int n : sizes) {
        // Measure execution time
        auto start = std::chrono::high_resolution_clock::now();
        
        fibonacci(n);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        
        results.push_back({n, duration.count()});
        std::cout << "Fibonacci(" << n << "): " 
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
    std::vector<int> sizes = {20, 30, 40};
    
    std::cout << "Running Fibonacci benchmark..." << std::endl;
    auto results = benchmark_fibonacci(sizes);
    
    // Save results
    save_results_to_csv(results, "../results/cpp_fibonacci_results.csv");
    
    return 0;
} 