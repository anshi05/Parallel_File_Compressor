#ifndef PROGRESSDASHBOARD_HPP
#define PROGRESSDASHBOARD_HPP

#include <QWidget>
#include <QLabel>
#include <QThread>

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
    void updatePerformanceGraph(double sequentialTime, double parallelTime);
    void reset();

private:
    void setupUI();

    // Stats labels
    QLabel* filesizeLabel = nullptr;
    QLabel* compressionRatioLabel = nullptr;
    QLabel* speedupLabel = nullptr;
    QLabel* timeLabel = nullptr;
    QLabel* threadsLabel = nullptr;

    // Performance chart (types from QtCharts headers above)
    QChartView* chartView = nullptr;
    QChart* chart = nullptr;
    QLineSeries* performanceSeries = nullptr;
};

#endif // PROGRESSDASHBOARD_HPP
