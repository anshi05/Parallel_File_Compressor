#include "benchmark.hpp"
#include "compressor.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

Benchmark::BenchmarkResult Benchmark::runBenchmark(const std::string& inputFile, 
                                                    int numThreads) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Running Parallel File Compressor Benchmark" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    int64_t fileSize = Utils::getFileSize(inputFile);
    if (fileSize <= 0) {
        std::cerr << "Error: Invalid file size" << std::endl;
        return {};
    }
    
    std::cout << "Input File: " << inputFile << std::endl;
    std::cout << "File Size: " << Utils::formatFileSize(fileSize) << std::endl;
    std::cout << "Threads Available: " << numThreads << "\n" << std::endl;
    
    // Sequential compression
    std::cout << "--- Sequential Compression (1 thread) ---" << std::endl;
    Utils::Timer seqTimer;
    seqTimer.start();
    Compressor seqCompressor(1);
    seqCompressor.compressFile(inputFile, "bench_seq.pfc", 1);
    seqTimer.stop();
    double seqTime = seqTimer.elapsedMs();
    int64_t seqSize = Utils::getFileSize("bench_seq.pfc");
    
    std::cout << "\n--- Parallel Compression (" << numThreads << " threads) ---" << std::endl;
    Utils::Timer parTimer;
    parTimer.start();
    Compressor parCompressor(numThreads);
    parCompressor.compressFile(inputFile, "bench_par.pfc", numThreads);
    parTimer.stop();
    double parTime = parTimer.elapsedMs();
    int64_t parSize = Utils::getFileSize("bench_par.pfc");
    
    BenchmarkResult result;
    result.sequentialTime = seqTime / 1000.0;
    result.parallelTime = parTime / 1000.0;
    result.speedup = seqTime / parTime;
    result.efficiency = (result.speedup / numThreads) * 100.0;
    result.originalSize = fileSize;
    result.compressedSize = parSize;
    
    return result;
}

void Benchmark::printResults(const BenchmarkResult& result, int numThreads) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "BENCHMARK RESULTS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::cout << std::left << std::setw(30) << "Sequential Time:" 
              << std::fixed << std::setprecision(3) << result.sequentialTime << " sec" << std::endl;
    std::cout << std::left << std::setw(30) << "Parallel Time (" << numThreads << " threads):" 
              << std::fixed << std::setprecision(3) << result.parallelTime << " sec" << std::endl;
    
    std::cout << "\n" << std::left << std::setw(30) << "Speedup:" 
              << std::fixed << std::setprecision(2) << result.speedup << "x" << std::endl;
    std::cout << std::left << std::setw(30) << "Parallel Efficiency:" 
              << std::fixed << std::setprecision(1) << result.efficiency << "%" << std::endl;
    
    std::cout << "\n" << std::left << std::setw(30) << "Original Size:" 
              << Utils::formatFileSize(result.originalSize) << std::endl;
    std::cout << std::left << std::setw(30) << "Compressed Size:" 
              << Utils::formatFileSize(result.compressedSize) << std::endl;
    std::cout << std::left << std::setw(30) << "Compression Ratio:" 
              << std::fixed << std::setprecision(2) 
              << Utils::calculateCompressionRatio(result.originalSize, result.compressedSize)
              << "%" << std::endl;
    
    std::cout << std::string(50, '=') << "\n" << std::endl;
}
