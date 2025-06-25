import random
import time

def quicksort(arr):
    """
    Implementation of the QuickSort algorithm
    """
    if len(arr) <= 1:
        return arr
    
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    
    return quicksort(left) + middle + quicksort(right)

def generate_random_array(size, min_val=1, max_val=1000):
    """
    Generate a random array of given size
    """
    return [random.randint(min_val, max_val) for _ in range(size)]

def benchmark_quicksort(sizes=[100, 1000, 10000]):
    """
    Benchmark QuickSort with different input sizes
    """
    results = []
    
    for size in sizes:
        # Generate random array
        arr = generate_random_array(size)
        
        # Measure execution time
        start_time = time.time()
        quicksort(arr.copy())  # Use copy to avoid modifying the original array
        execution_time = time.time() - start_time
        
        results.append((size, execution_time))
        print(f"QuickSort with array size {size}: {execution_time:.6f} seconds")
    
    return results

if __name__ == "__main__":
    # Example usage
    benchmark_quicksort([1000, 100000, 1000000]) 