#ifndef DECOMPRESSOR_HPP
#define DECOMPRESSOR_HPP

#include "utils.hpp"
#include <string>
#include <vector>

class Decompressor {
public:
    Decompressor(int threadCount = 0);
    
    // Decompress a .pfc file
    bool decompressFile(const std::string& compressedFile,
                       const std::string& outputFile = "");
    
    // Decompress a single chunk
    static std::vector<uint8_t> decompressChunk(const std::vector<uint8_t>& input, 
                                                 uint64_t expectedSize = 0);
    
private:
    int threadCount;
    
    // Helper methods
    bool readMetadata(const std::string& filename, FileMetadata& metadata);
    bool readAndDecompressChunks(const std::string& compressedFile,
                                const FileMetadata& metadata,
                                std::vector<std::vector<uint8_t>>& decompressedChunks);
};

#endif // DECOMPRESSOR_HPP
