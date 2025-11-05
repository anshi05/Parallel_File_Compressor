#include "compressor.hpp"
#include "decompressor.hpp"
#include "benchmark.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <cstring>

void printUsage(const char* programName) {
    std::cout << "\nParallel File Compressor - Usage Guide\n" << std::endl;
    std::cout << "Usage: " << programName << " [COMMAND] [OPTIONS]\n" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  --compress <input_file> [output_file]" << std::endl;
    std::cout << "      Compress a file using parallel processing" << std::endl;
    std::cout << "      Optional: specify custom output filename" << std::endl;
    std::cout << std::endl;
    std::cout << "  --decompress <compressed_file> [output_file]" << std::endl;
    std::cout << "      Decompress a .pfc file" << std::endl;
    std::cout << "      Optional: specify custom output filename" << std::endl;
    std::cout << std::endl;
    std::cout << "  --benchmark <input_file>" << std::endl;
    std::cout << "      Compare sequential vs parallel compression performance" << std::endl;
    std::cout << std::endl;
    std::cout << "Global Options:" << std::endl;
    std::cout << "  --threads <n>       Specify number of threads (default: auto-detect)" << std::endl;
    std::cout << "  --help              Display this help message" << std::endl;
    std::cout << "\nExamples:" << std::endl;
    std::cout << "  " << programName << " --compress myfile.txt" << std::endl;
    std::cout << "  " << programName << " --compress data.bin archive.pfc --threads 8" << std::endl;
    std::cout << "  " << programName << " --decompress archive.pfc" << std::endl;
    std::cout << "  " << programName << " --benchmark largefile.iso" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string command = argv[1];
    int threadCount = Utils::getOptimalThreadCount();
    
    // Parse global options
    for (int i = 2; i < argc; i++) {
        if (std::string(argv[i]) == "--threads" && i + 1 < argc) {
            threadCount = std::atoi(argv[i + 1]);
            if (threadCount <= 0) threadCount = 1;
            i++;
        } else if (std::string(argv[i]) == "--help") {
            printUsage(argv[0]);
            return 0;
        }
    }
    
    try {
        if (command == "--compress") {
            if (argc < 3) {
                std::cerr << "Error: --compress requires an input file" << std::endl;
                printUsage(argv[0]);
                return 1;
            }
            
            std::string inputFile = argv[2];
            std::string outputFile = (argc > 3 && argv[3][0] != '-') ? argv[3] : 
                                    inputFile + ".pfc";
            
            Compressor compressor(threadCount);
            if (compressor.compressFile(inputFile, outputFile)) {
                return 0;
            } else {
                return 1;
            }
        }
        else if (command == "--decompress") {
            if (argc < 3) {
                std::cerr << "Error: --decompress requires a compressed file" << std::endl;
                printUsage(argv[0]);
                return 1;
            }
            
            std::string compressedFile = argv[2];
            std::string outputFile = (argc > 3 && argv[3][0] != '-') ? argv[3] : "";
            
            Decompressor decompressor(threadCount);
            if (decompressor.decompressFile(compressedFile, outputFile)) {
                return 0;
            } else {
                return 1;
            }
        }
        else if (command == "--benchmark") {
            if (argc < 3) {
                std::cerr << "Error: --benchmark requires an input file" << std::endl;
                printUsage(argv[0]);
                return 1;
            }
            
            std::string inputFile = argv[2];
            auto result = Benchmark::runBenchmark(inputFile, threadCount);
            Benchmark::printResults(result, threadCount);
            return 0;
        }
        else if (command == "--help") {
            printUsage(argv[0]);
            return 0;
        }
        else {
            std::cerr << "Error: Unknown command '" << command << "'" << std::endl;
            printUsage(argv[0]);
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
