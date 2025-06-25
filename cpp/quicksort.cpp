#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

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
std::vector<int> generate_random_array(int size, int min_val = 1, int max_val = 1000) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min_val, max_val);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

// Benchmark QuickSort
std::vector<std::pair<int, double>> benchmark_quicksort(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    
    for (int size : sizes) {
        // Generate random array
        std::vector<int> arr = generate_random_array(size);
        
        // Measure execution time
        auto start = std::chrono::high_resolution_clock::now();
        
        std::vector<int> arr_copy = arr; // Create a copy to sort
        quicksort(arr_copy);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        
        results.push_back({size, duration.count()});
        std::cout << "QuickSort with array size " << size << ": " 
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
    std::vector<int> sizes = {1000, 100000, 1000000};
    
    std::cout << "Running QuickSort benchmark..." << std::endl;
    auto results = benchmark_quicksort(sizes);
    
    // Save results
    save_results_to_csv(results, "../results/cpp_quicksort_results.csv");
    
    return 0;
} 