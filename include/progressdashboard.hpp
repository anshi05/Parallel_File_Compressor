#ifndef PROGRESSDASHBOARD_HPP
#define PROGRESSDASHBOARD_HPP

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QGroupBox>

// QtCharts public headers
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

// Use unqualified QtCharts class names (they are available via these headers)
class ProgressDashboard : public QWidget {
    Q_OBJECT

public:
    explicit ProgressDashboard(QWidget* parent = nullptr);

    void updateStats(uint64_t originalSize, uint64_t compressedSize,
                     double compressionRatio, double speedup, double timeMs);
    void updateBenchmarkStats(uint64_t originalSize, uint64_t compressedSize,
                              double compressionRatio, double sequentialTime,
                              double parallelTime, double speedup, double efficiency);
    void updatePerformanceGraph(double sequentialTime, double parallelTime);
    void setStatisticsTitle(const QString& title);
    void setRatioLabel(const QString& label);
    void setThreadCount(int count);
    void reset();

private:
    void setupUI();

    // Stats group box and labels
    QGroupBox* statsGroup = nullptr;
    QLabel* filesizeLabel = nullptr;
    QLabel* compressionRatioLabel = nullptr;
    QLabel* ratioLabel = nullptr;  // "Compression Ratio:" or "Decompression Ratio:" label
    QLabel* speedupLabel = nullptr;
    QLabel* timeLabel = nullptr;
    QLabel* threadsLabel = nullptr;
    // Benchmark-specific labels
    QLabel* sequentialTimeLabel = nullptr;
    QLabel* parallelTimeLabel = nullptr;
    QLabel* efficiencyLabel = nullptr;
    QLabel* sequentialTimeLabelText = nullptr;
    QLabel* parallelTimeLabelText = nullptr;
    QLabel* efficiencyLabelText = nullptr;

    // Performance chart (types from QtCharts headers above)
    QChartView* chartView = nullptr;
    QChart* chart = nullptr;
    QLineSeries* performanceSeries = nullptr;
};

#endif // PROGRESSDASHBOARD_HPP
