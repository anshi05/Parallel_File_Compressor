#include "compressor.hpp"
#include <fstream>
#include <zlib.h>
#include <omp.h>
#include <cstring>

Compressor::Compressor(int threadCount) 
    : threadCount(threadCount > 0 ? threadCount : Utils::getOptimalThreadCount()) {
    omp_set_num_threads(this->threadCount);
}

std::vector<uint8_t> Compressor::compressChunk(const std::vector<uint8_t>& input) {
    std::vector<uint8_t> output;
    if (input.empty()) return output;
    
    // Allocate worst-case buffer
    uLongf compressedSize = compressBound(input.size());
    output.resize(compressedSize);
    
    int ret = compress2(output.data(), &compressedSize, 
                       input.data(), input.size(), 9);
    
    if (ret == Z_OK) {
        output.resize(compressedSize);
    } else {
        output.clear();
    }
    
    return output;
}

bool Compressor::splitAndCompressChunks(const std::string& inputFile,
                                        std::vector<std::vector<uint8_t>>& compressedChunks,
                                        int numChunks) {
    std::ifstream infile(inputFile, std::ios::binary);
    if (!infile) {
        std::cerr << "Error: Cannot open input file " << inputFile << std::endl;
        return false;
    }
    
    infile.seekg(0, std::ios::end);
    uint64_t fileSize = infile.tellg();
    infile.seekg(0, std::ios::beg);
    
    if (numChunks <= 0) {
        numChunks = (fileSize + CHUNK_SIZE - 1) / CHUNK_SIZE;
    }
    
    uint64_t chunkSize = (fileSize + numChunks - 1) / numChunks;
    std::vector<std::vector<uint8_t>> chunks(numChunks);
    
    Utils::ProgressTracker progress(fileSize, "Reading");
    
    // Read chunks
    for (int i = 0; i < numChunks; i++) {
        uint64_t readSize = std::min(chunkSize, fileSize - i * chunkSize);
        chunks[i].resize(readSize);
        infile.read(reinterpret_cast<char*>(chunks[i].data()), readSize);
        progress.update((i + 1) * chunkSize);
    }
    progress.complete();
    infile.close();
    
    // Compress chunks in parallel
    compressedChunks.resize(numChunks);
    
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < numChunks; i++) {
        #pragma omp critical
        std::cout << "[Thread " << omp_get_thread_num() << "] Compressing chunk " 
                  << (i + 1) << "/" << numChunks << std::endl;
        
        compressedChunks[i] = compressChunk(chunks[i]);
    }
    
    return true;
}

bool Compressor::writeCompressedFile(const std::string& outputFile,
                                     const std::string& originalFilename,
                                     const std::vector<std::vector<uint8_t>>& chunks,
                                     uint64_t originalSize) {
    std::ofstream outfile(outputFile, std::ios::binary);
    if (!outfile) {
        std::cerr << "Error: Cannot create output file " << outputFile << std::endl;
        return false;
    }
    
    FileMetadata metadata;
    metadata.originalSize = originalSize;
    metadata.numChunks = chunks.size();
    metadata.algorithm = 0; // zlib
    strncpy(metadata.originalFilename, originalFilename.c_str(), 255);
    
    // Calculate offsets
    uint64_t dataOffset = sizeof(FileMetadata) + (chunks.size() * sizeof(uint64_t) * 2);
    uint64_t currentOffset = dataOffset;
    
    for (size_t i = 0; i < chunks.size(); i++) {
        metadata.chunkOffsets.push_back(currentOffset);
        metadata.chunkSizes.push_back(chunks[i].size());
        currentOffset += chunks[i].size();
    }
    
    // Write metadata
    outfile.write(reinterpret_cast<const char*>(&metadata.magic), sizeof(metadata.magic));
    outfile.write(reinterpret_cast<const char*>(&metadata.version), sizeof(metadata.version));
    outfile.write(reinterpret_cast<const char*>(&metadata.originalSize), sizeof(metadata.originalSize));
    outfile.write(reinterpret_cast<const char*>(&metadata.numChunks), sizeof(metadata.numChunks));
    outfile.write(reinterpret_cast<const char*>(&metadata.algorithm), sizeof(metadata.algorithm));
    outfile.write(metadata.originalFilename, 256);
    
    // Write offsets and sizes
    for (size_t i = 0; i < chunks.size(); i++) {
        outfile.write(reinterpret_cast<const char*>(&metadata.chunkOffsets[i]), sizeof(uint64_t));
    }
    for (size_t i = 0; i < chunks.size(); i++) {
        outfile.write(reinterpret_cast<const char*>(&metadata.chunkSizes[i]), sizeof(uint32_t));
    }
    
    // Write compressed chunks
    Utils::ProgressTracker progress(currentOffset - dataOffset, "Writing");
    for (size_t i = 0; i < chunks.size(); i++) {
        outfile.write(reinterpret_cast<const char*>(chunks[i].data()), chunks[i].size());
        progress.update((i + 1) * (chunks[0].size() > 0 ? chunks[0].size() : 1));
    }
    progress.complete();
    
    outfile.close();
    return true;
}

bool Compressor::compressFile(const std::string& inputFile, 
                             const std::string& outputFile,
                             int numChunks) {
    if (!Utils::fileExists(inputFile)) {
        std::cerr << "Error: Input file not found: " << inputFile << std::endl;
        return false;
    }
    
    int64_t fileSize = Utils::getFileSize(inputFile);
    if (fileSize <= 0) {
        std::cerr << "Error: Invalid file size" << std::endl;
        return false;
    }
    
    std::cout << "\nCompressing " << inputFile << " (" 
              << Utils::formatFileSize(fileSize) << ") with " 
              << threadCount << " threads..." << std::endl;
    
    std::vector<std::vector<uint8_t>> compressedChunks;
    if (!splitAndCompressChunks(inputFile, compressedChunks, numChunks)) {
        return false;
    }
    
    uint64_t compressedSize = 0;
    for (const auto& chunk : compressedChunks) {
        compressedSize += chunk.size();
    }
    
    if (!writeCompressedFile(outputFile, inputFile, compressedChunks, fileSize)) {
        return false;
    }
    
    uint64_t totalOutputSize = Utils::getFileSize(outputFile);
    std::cout << "\nCompression completed!" << std::endl;
    std::cout << "Output file: " << outputFile << std::endl;
    Utils::printCompressionStats(fileSize, totalOutputSize, 0, threadCount);
    
    return true;
}
