CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lstdc++fs

SRCS = quicksort.cpp fibonacci.cpp matrix_mult.cpp benchmark.cpp
EXECS = quicksort fibonacci matrix_mult benchmark

all: $(EXECS)

quicksort: quicksort.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

fibonacci: fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

matrix_mult: matrix_mult.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

benchmark: benchmark.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(EXECS)

.PHONY: all clean 