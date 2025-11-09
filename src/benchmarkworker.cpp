#include "benchmarkworker.hpp"
#include <QDebug>

BenchmarkWorker::BenchmarkWorker() {}

void BenchmarkWorker::runBenchmark(const QString& inputFile, int threadCount) {
    try {
        emit progressUpdated("Running sequential compression...");
        
        Benchmark::BenchmarkResult result = Benchmark::runBenchmark(inputFile.toStdString(), threadCount);
        
        emit progressUpdated("Benchmark complete!");
        emit benchmarkFinished(result.sequentialTime, result.parallelTime, 
                            result.speedup, result.efficiency,
                            result.originalSize, result.compressedSize);
    } catch (const std::exception& e) {
        emit errorOccurred(QString("Exception: %1").arg(e.what()));
    }
}
