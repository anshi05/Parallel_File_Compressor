#ifndef COMPRESSIONWORKER_HPP
#define COMPRESSIONWORKER_HPP

#include <QObject>
#include <QString>
#include <vector>
#include "compressor.hpp"

class CompressionWorker : public QObject {
    Q_OBJECT
public:
    CompressionWorker();
    ~CompressionWorker();
    
public slots:
    void compress(const QString& inputFile, const QString& outputFile, int threadCount);
    
signals:
    void progressUpdated(int percentage, const QString& status);
    void compressionFinished(bool success, const QString& message, 
                           uint64_t originalSize, uint64_t compressedSize, double timeMs);
    void chunkProcessed(int chunkIndex, int totalChunks);
    void errorOccurred(const QString& error);
    
private:
    Compressor* compressor;
};

#endif // COMPRESSIONWORKER_HPP
