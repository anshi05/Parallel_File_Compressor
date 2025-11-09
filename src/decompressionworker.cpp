#include "decompressionworker.hpp"
#include <QDebug>

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
        
        if (decompressor->decompressFile(inputFile.toStdString(), outputFile.toStdString())) {
            emit progressUpdated(100, "Decompression complete!");
            emit decompressionFinished(true, 
                                     QString("File decompressed successfully to %1").arg(outputFile),
                                     0.0);
        } else {
            emit decompressionFinished(false, "Decompression failed", 0.0);
        }
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Exception: %1").arg(e.what()));
    }
}
