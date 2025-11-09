#ifndef BENCHMARKWORKER_HPP
#define BENCHMARKWORKER_HPP

#include <QObject>
#include <QString>
#include "benchmark.hpp"

class BenchmarkWorker : public QObject {
    Q_OBJECT
public:
    BenchmarkWorker();
    
public slots:
    void runBenchmark(const QString& inputFile, int threadCount);
    
signals:
    void progressUpdated(const QString& status);
    void benchmarkFinished(double sequentialTime, double parallelTime, 
                          double speedup, double efficiency, 
                          uint64_t originalSize, uint64_t compressedSize);
    void errorOccurred(const QString& error);
    
private:
};

#endif // BENCHMARKWORKER_HPP
