#include "compressionworker.hpp"
#include <QDebug>

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
        
        if (compressor->compressFile(inputFile.toStdString(), outputFile.toStdString())) {
            emit progressUpdated(100, "Compression complete!");
            emit compressionFinished(true, 
                                   QString("File compressed successfully to %1").arg(outputFile),
                                   0, 0, 0.0);
        } else {
            emit compressionFinished(false, "Compression failed", 0, 0, 0.0);
        }
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Exception: %1").arg(e.what()));
    }
}
