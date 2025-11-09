#include "decompressor.hpp"
#include <fstream>
#include <zlib.h>
#include <omp.h>
#include <cstring>

Decompressor::Decompressor(int threadCount)
    : threadCount(threadCount > 0 ? threadCount : Utils::getOptimalThreadCount()) {
    omp_set_num_threads(this->threadCount);
}

std::vector<uint8_t> Decompressor::decompressChunk(const std::vector<uint8_t>& input, 
                                                      uint64_t expectedSize) {
    std::vector<uint8_t> output;
    if (input.empty()) return output;
    
    // Use expected size if provided, otherwise estimate
    uLongf decompressedSize;
    if (expectedSize > 0) {
        decompressedSize = expectedSize + (expectedSize / 10); // Add 10% buffer
    } else {
        decompressedSize = input.size() * 20; // Fallback estimation
    }
    output.resize(decompressedSize);
    
    int ret = uncompress(output.data(), &decompressedSize, 
                        input.data(), input.size());
    
    if (ret == Z_OK) {
        output.resize(decompressedSize);
    } else if (ret == Z_BUF_ERROR) {
        // Buffer too small, retry with larger buffer
        if (expectedSize > 0) {
            decompressedSize = expectedSize * 2; // Double the expected size
        } else {
            decompressedSize = input.size() * 50; // Fallback
        }
        output.resize(decompressedSize);
        ret = uncompress(output.data(), &decompressedSize, 
                        input.data(), input.size());
        if (ret == Z_OK) {
            output.resize(decompressedSize);
        } else {
            std::cerr << "Error: Decompression failed with code " << ret << std::endl;
            output.clear();
        }
    } else {
        std::cerr << "Error: Decompression failed with code " << ret << std::endl;
        output.clear();
    }
    
    return output;
}

bool Decompressor::readMetadata(const std::string& filename, FileMetadata& metadata) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile) {
        std::cerr << "Error: Cannot open compressed file" << std::endl;
        return false;
    }
    
    infile.read(reinterpret_cast<char*>(&metadata.magic), sizeof(metadata.magic));
    if (metadata.magic != FileMetadata::MAGIC) {
        std::cerr << "Error: Invalid .pfc file format" << std::endl;
        return false;
    }
    
    infile.read(reinterpret_cast<char*>(&metadata.version), sizeof(metadata.version));
    infile.read(reinterpret_cast<char*>(&metadata.originalSize), sizeof(metadata.originalSize));
    infile.read(reinterpret_cast<char*>(&metadata.numChunks), sizeof(metadata.numChunks));
    infile.read(reinterpret_cast<char*>(&metadata.algorithm), sizeof(metadata.algorithm));
    infile.read(metadata.originalFilename, 256);
    
    metadata.chunkOffsets.resize(metadata.numChunks);
    metadata.chunkSizes.resize(metadata.numChunks);
    
    for (uint32_t i = 0; i < metadata.numChunks; i++) {
        infile.read(reinterpret_cast<char*>(&metadata.chunkOffsets[i]), sizeof(uint64_t));
    }
    for (uint32_t i = 0; i < metadata.numChunks; i++) {
        infile.read(reinterpret_cast<char*>(&metadata.chunkSizes[i]), sizeof(uint32_t));
    }
    
    infile.close();
    return true;
}

bool Decompressor::readAndDecompressChunks(const std::string& compressedFile,
                                          const FileMetadata& metadata,
                                          std::vector<std::vector<uint8_t>>& decompressedChunks) {
    std::ifstream infile(compressedFile, std::ios::binary);
    if (!infile) {
        std::cerr << "Error: Cannot open compressed file" << std::endl;
        return false;
    }
    
    std::vector<std::vector<uint8_t>> compressedChunks(metadata.numChunks);
    
    // Calculate approximate original chunk size
    uint64_t approxChunkSize = (metadata.originalSize + metadata.numChunks - 1) / metadata.numChunks;
    
    // Read compressed chunks
    Utils::ProgressTracker progress(metadata.originalSize, "Reading compressed data");
    for (uint32_t i = 0; i < metadata.numChunks; i++) {
        infile.seekg(metadata.chunkOffsets[i]);
        compressedChunks[i].resize(metadata.chunkSizes[i]);
        infile.read(reinterpret_cast<char*>(compressedChunks[i].data()), metadata.chunkSizes[i]);
        progress.update((i + 1) * (metadata.originalSize / metadata.numChunks));
    }
    progress.complete();
    infile.close();
    
    // Decompress chunks in parallel
    decompressedChunks.resize(metadata.numChunks);
    
    #pragma omp parallel for schedule(dynamic)
    for (uint32_t i = 0; i < metadata.numChunks; i++) {
        #pragma omp critical
        std::cout << "[Thread " << omp_get_thread_num() << "] Decompressing chunk " 
                  << (i + 1) << "/" << metadata.numChunks << std::endl;
        
        // Use approximate chunk size for better buffer estimation
        decompressedChunks[i] = decompressChunk(compressedChunks[i], approxChunkSize);
    }
    
    return true;
}

bool Decompressor::decompressFile(const std::string& compressedFile,
                                 const std::string& outputFile) {
    FileMetadata metadata;
    if (!readMetadata(compressedFile, metadata)) {
        return false;
    }
    
    std::string outFile = outputFile.empty() ? metadata.originalFilename : outputFile;
    
    std::cout << "\nDecompressing " << compressedFile << std::endl;
    std::cout << "Original file: " << metadata.originalFilename 
              << " (" << Utils::formatFileSize(metadata.originalSize) << ")" << std::endl;
    std::cout << "Number of chunks: " << metadata.numChunks << std::endl;
    
    std::vector<std::vector<uint8_t>> decompressedChunks;
    if (!readAndDecompressChunks(compressedFile, metadata, decompressedChunks)) {
        return false;
    }
    
    std::ofstream outfile(outFile, std::ios::binary);
    if (!outfile) {
        std::cerr << "Error: Cannot create output file" << std::endl;
        return false;
    }
    
    Utils::ProgressTracker progress(metadata.originalSize, "Writing");
    uint64_t totalWritten = 0;
    
    for (const auto& chunk : decompressedChunks) {
        outfile.write(reinterpret_cast<const char*>(chunk.data()), chunk.size());
        totalWritten += chunk.size();
        progress.update(totalWritten);
    }
    progress.complete();
    
    outfile.close();
    std::cout << "\nDecompression completed! Output: " << outFile << std::endl;
    
    return true;
}
