#include "benchmarkworker.hpp"
#include <QDebug>

BenchmarkWorker::BenchmarkWorker() {}

void BenchmarkWorker::runBenchmark(const QString& inputFile, int threadCount) {
    try {
        emit progressUpdated("Running sequential compression (1 thread)...");
        
        Benchmark::BenchmarkResult result = Benchmark::runBenchmark(inputFile.toStdString(), threadCount);
        
        emit progressUpdated(QString("Sequential: %1s, Parallel: %2s").arg(result.sequentialTime, 0, 'f', 3).arg(result.parallelTime, 0, 'f', 3));
        emit progressUpdated("Benchmark complete!");
        
        emit benchmarkFinished(result.sequentialTime * 1000.0, result.parallelTime * 1000.0, 
                            result.speedup, result.efficiency,
                            result.originalSize, result.compressedSize);
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Exception: %1").arg(e.what()));
    }
}
