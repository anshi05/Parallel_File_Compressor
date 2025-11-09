#include "compressionworker.hpp"
#include "utils.hpp"
#include <QDebug>
#include <QFileInfo>

CompressionWorker::CompressionWorker()
    : compressor(nullptr)
{
    compressor = new Compressor();
}

CompressionWorker::~CompressionWorker() {
    delete compressor;
}

void CompressionWorker::compress(const QString& inputFile, const QString& outputFile, int threadCount) {
    try {
        if (compressor) {
            delete compressor;
        }
        compressor = new Compressor(threadCount);
        
        emit progressUpdated(10, "Preparing compression...");
        
        // Get original file size
        uint64_t originalSize = Utils::getFileSize(inputFile.toStdString());
        if (originalSize == 0) {
            emit compressionFinished(false, "Invalid input file size", 0, 0, 0.0);
            return;
        }
        
        // Start timing
        Utils::Timer timer;
        timer.start();
        
        emit progressUpdated(20, "Compressing file...");
        
        if (compressor->compressFile(inputFile.toStdString(), outputFile.toStdString())) {
            timer.stop();
            double elapsedMs = timer.elapsedMs();
            
            // Get compressed file size
            uint64_t compressedSize = Utils::getFileSize(outputFile.toStdString());
            
            emit progressUpdated(100, "Compression complete!");
            emit compressionFinished(true, 
                                   QString("File compressed successfully to %1").arg(outputFile),
                                   originalSize, compressedSize, elapsedMs);
        } else {
            emit compressionFinished(false, "Compression failed", 0, 0, 0.0);
        }
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Exception: %1").arg(e.what()));
    }
}
