#ifndef DECOMPRESSIONWORKER_HPP
#define DECOMPRESSIONWORKER_HPP

#include <QObject>
#include <QString>
#include "decompressor.hpp"

class DecompressionWorker : public QObject {
    Q_OBJECT
public:
    DecompressionWorker();
    ~DecompressionWorker();
    
public slots:
    void decompress(const QString& inputFile, const QString& outputFile, int threadCount);
    
signals:
    void progressUpdated(int percentage, const QString& status);
    void decompressionFinished(bool success, const QString& message, double timeMs,
                               uint64_t compressedSize, uint64_t decompressedSize);
    void chunkProcessed(int chunkIndex, int totalChunks);
    void errorOccurred(const QString& error);
    
private:
    Decompressor* decompressor;
};

#endif // DECOMPRESSIONWORKER_HPP
