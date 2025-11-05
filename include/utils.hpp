#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>

struct FileMetadata {
    static constexpr uint32_t MAGIC = 0x50464331; // "PFC1"
    uint32_t magic;
    uint32_t version;
    uint64_t originalSize;
    uint32_t numChunks;
    uint32_t algorithm; // 0 = zlib
    char originalFilename[256];
    std::vector<uint64_t> chunkOffsets;
    std::vector<uint32_t> chunkSizes;

    FileMetadata() : magic(MAGIC), version(1), originalSize(0), 
                     numChunks(0), algorithm(0) {
        memset(originalFilename, 0, 256);
    }
};

// Utility functions
namespace Utils {
    // File operations
    int64_t getFileSize(const std::string& filename);
    bool fileExists(const std::string& filename);
    int getOptimalThreadCount();
    
    // Progress tracking
    class ProgressTracker {
    public:
        ProgressTracker(uint64_t total, const std::string& prefix = "");
        void update(uint64_t current);
        void complete();
        
    private:
        uint64_t total;
        uint64_t lastPrinted;
        std::string prefix;
    };
    
    // Timing utilities
    class Timer {
    public:
        Timer();
        void start();
        void stop();
        double elapsedMs() const;
        double elapsedSec() const;
        void printElapsed(const std::string& label) const;
        
    private:
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;
    };
    
    // String utilities
    std::string formatFileSize(uint64_t bytes);
    double calculateCompressionRatio(uint64_t originalSize, uint64_t compressedSize);
    void printCompressionStats(uint64_t originalSize, uint64_t compressedSize, 
                               double timeMs, int threads);
}

#endif // UTILS_HPP
