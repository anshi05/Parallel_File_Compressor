#include "decompressionworker.hpp"
#include "utils.hpp"
#include <QDebug>
#include <QFileInfo>
#include <fstream>

DecompressionWorker::DecompressionWorker()
    : decompressor(nullptr)
{
    decompressor = new Decompressor();
}

DecompressionWorker::~DecompressionWorker() {
    delete decompressor;
}

void DecompressionWorker::decompress(const QString& inputFile, const QString& outputFile, int threadCount) {
    try {
        if (decompressor) {
            delete decompressor;
        }
        decompressor = new Decompressor(threadCount);
        
        emit progressUpdated(10, "Preparing decompression...");
        
        // Get compressed file size
        uint64_t compressedSize = Utils::getFileSize(inputFile.toStdString());
        if (compressedSize == 0) {
            emit decompressionFinished(false, "Invalid compressed file size", 0.0, 0, 0);
            return;
        }
        
        // Start timing
        Utils::Timer timer;
        timer.start();
        
        emit progressUpdated(20, "Decompressing file...");
        
        // Read metadata to get original file size
        FileMetadata metadata;
        std::ifstream infile(inputFile.toStdString(), std::ios::binary);
        if (infile) {
            infile.read(reinterpret_cast<char*>(&metadata.magic), sizeof(metadata.magic));
            if (metadata.magic == FileMetadata::MAGIC) {
                infile.read(reinterpret_cast<char*>(&metadata.version), sizeof(metadata.version));
                infile.read(reinterpret_cast<char*>(&metadata.originalSize), sizeof(metadata.originalSize));
                infile.read(reinterpret_cast<char*>(&metadata.numChunks), sizeof(metadata.numChunks));
                infile.read(reinterpret_cast<char*>(&metadata.algorithm), sizeof(metadata.algorithm));
                infile.read(metadata.originalFilename, 256);
            }
            infile.close();
        }
        
        // Determine actual output file path
        std::string actualOutputFile = outputFile.toStdString();
        if (actualOutputFile.empty()) {
            // Decompressor will use original filename from metadata
            actualOutputFile = std::string(metadata.originalFilename);
        }
        
        if (decompressor->decompressFile(inputFile.toStdString(), actualOutputFile)) {
            timer.stop();
            double elapsedMs = timer.elapsedMs();
            
            // Get decompressed file size (use original size from metadata if available)
            uint64_t decompressedSize = metadata.originalSize > 0 ? metadata.originalSize : Utils::getFileSize(actualOutputFile);
            
            emit progressUpdated(100, "Decompression complete!");
            emit decompressionFinished(true, 
                                     QString("File decompressed successfully to %1").arg(QString::fromStdString(actualOutputFile)),
                                     elapsedMs, compressedSize, decompressedSize);
        } else {
            emit decompressionFinished(false, "Decompression failed", 0.0, 0, 0);
        }
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Exception: %1").arg(e.what()));
    }
}
