#ifndef COMPRESSOR_HPP
#define COMPRESSOR_HPP

#include "utils.hpp"
#include <vector>
#include <string>
#include <memory>

class Compressor {
public:
    Compressor(int threadCount = 0);
    
    // Compress a file with parallel chunk processing
    bool compressFile(const std::string& inputFile, 
                     const std::string& outputFile,
                     int numChunks = 0);
    
    // Compress a single chunk
    static std::vector<uint8_t> compressChunk(const std::vector<uint8_t>& input);
    
private:
    int threadCount;
    const size_t CHUNK_SIZE = 1024 * 1024; // 1MB chunks
    
    // Helper methods
    bool splitAndCompressChunks(const std::string& inputFile,
                                std::vector<std::vector<uint8_t>>& compressedChunks,
                                int numChunks);
    bool writeCompressedFile(const std::string& outputFile,
                            const std::string& originalFilename,
                            const std::vector<std::vector<uint8_t>>& chunks,
                            uint64_t originalSize);
};

#endif // COMPRESSOR_HPP
