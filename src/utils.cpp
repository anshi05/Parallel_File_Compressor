#include "utils.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <thread>

namespace Utils {
    
int64_t getFileSize(const std::string& filename) {
    struct stat statbuf;
    if (stat(filename.c_str(), &statbuf) == -1) {
        return -1;
    }
    return statbuf.st_size;
}

bool fileExists(const std::string& filename) {
    return access(filename.c_str(), F_OK) != -1;
}

int getOptimalThreadCount() {
    int count = std::thread::hardware_concurrency();
    return count > 0 ? count : 4;
}

std::string formatFileSize(uint64_t bytes) {
    const char* units[] = {"B", "KB", "MB", "GB"};
    double size = static_cast<double>(bytes);
    int unitIdx = 0;
    
    while (size > 1024.0 && unitIdx < 3) {
        size /= 1024.0;
        unitIdx++;
    }
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << size << " " << units[unitIdx];
    return ss.str();
}

double calculateCompressionRatio(uint64_t originalSize, uint64_t compressedSize) {
    if (originalSize == 0) return 0.0;
    return (1.0 - static_cast<double>(compressedSize) / originalSize) * 100.0;
}

void printCompressionStats(uint64_t originalSize, uint64_t compressedSize, 
                          double timeMs, int threads) {
    std::cout << "\n=== Compression Statistics ===" << std::endl;
    std::cout << "  Original Size:     " << formatFileSize(originalSize) << std::endl;
    std::cout << "  Compressed Size:   " << formatFileSize(compressedSize) << std::endl;
    std::cout << "  Compression Ratio: " 
              << std::fixed << std::setprecision(2) 
              << calculateCompressionRatio(originalSize, compressedSize) << "%" << std::endl;
    std::cout << "  Time Taken:        " << std::fixed << std::setprecision(3) 
              << (timeMs / 1000.0) << " seconds" << std::endl;
    std::cout << "  Throughput:        " 
              << std::fixed << std::setprecision(2)
              << (originalSize / (timeMs / 1000.0) / 1024 / 1024) << " MB/s" << std::endl;
    std::cout << "  Threads Used:      " << threads << std::endl;
    std::cout << "============================\n" << std::endl;
}

// ProgressTracker implementation
ProgressTracker::ProgressTracker(uint64_t total, const std::string& prefix)
    : total(total), lastPrinted(0), prefix(prefix) {}

void ProgressTracker::update(uint64_t current) {
    if (total == 0) return;
    
    uint64_t percentage = (current * 100) / total;
    if (percentage - lastPrinted >= 5 || current == total) {
        std::cout << "\r" << prefix << " Progress: " << percentage << "% (" 
                  << Utils::formatFileSize(current) << " / " 
                  << Utils::formatFileSize(total) << ")" << std::flush;
        lastPrinted = percentage;
    }
}

void ProgressTracker::complete() {
    std::cout << "\r" << prefix << " Progress: 100% (" 
              << Utils::formatFileSize(total) << " / " 
              << Utils::formatFileSize(total) << ")" << std::endl;
}

// Timer implementation
Timer::Timer() : startTime(), endTime() {}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
}

double Timer::elapsedMs() const {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTime - startTime);
    return duration.count();
}

double Timer::elapsedSec() const {
    return elapsedMs() / 1000.0;
}

void Timer::printElapsed(const std::string& label) const {
    std::cout << label << ": " << std::fixed << std::setprecision(3) 
              << elapsedSec() << " seconds" << std::endl;
}

} // namespace Utils
