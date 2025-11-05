#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "utils.hpp"
#include <string>

class Benchmark {
public:
    struct BenchmarkResult {
        double sequentialTime;
        double parallelTime;
        double speedup;
        double efficiency;
        uint64_t originalSize;
        uint64_t compressedSize;
    };
    
    // Run benchmark comparing sequential vs parallel compression
    static BenchmarkResult runBenchmark(const std::string& inputFile, 
                                       int numThreads);
    
    // Print benchmark results in a formatted table
    static void printResults(const BenchmarkResult& result, int numThreads);
    
private:
    static BenchmarkResult sequentialCompress(const std::string& inputFile);
    static BenchmarkResult parallelCompress(const std::string& inputFile, 
                                           int numThreads);
};

#endif // BENCHMARK_HPP
