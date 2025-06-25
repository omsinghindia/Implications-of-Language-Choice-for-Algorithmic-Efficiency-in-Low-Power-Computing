import time

def fibonacci(n):
    """
    Recursive implementation of Fibonacci sequence
    """
    if n <= 1:
        return n
    return fibonacci(n-1) + fibonacci(n-2)

def benchmark_fibonacci(sizes=[10, 20, 30]):
    """
    Benchmark Fibonacci with different input sizes
    """
    results = []
    
    for n in sizes:
        # Measure execution time
        start_time = time.time()
        fibonacci(n)
        execution_time = time.time() - start_time
        
        results.append((n, execution_time))
        print(f"Fibonacci({n}): {execution_time:.6f} seconds")
    
    return results

if __name__ == "__main__":
    # Example usage
    benchmark_fibonacci([20, 30, 40]) 