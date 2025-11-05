#ifndef PROGRESSDASHBOARD_HPP
#define PROGRESSDASHBOARD_HPP

#include <QWidget>
#include <QLabel>
#include <QChartView>
#include <QChart>
#include <QLineSeries>

class ProgressDashboard : public QWidget {
    Q_OBJECT
    
public:
    ProgressDashboard(QWidget* parent = nullptr);
    
    void updateStats(uint64_t originalSize, uint64_t compressedSize, 
                    double compressionRatio, double speedup, double timeMs);
    void updatePerformanceGraph(double sequentialTime, double parallelTime);
    void reset();
    
private:
    void setupUI();
    
    // Stats labels
    QLabel* filesizeLabel;
    QLabel* compressionRatioLabel;
    QLabel* speedupLabel;
    QLabel* timeLabel;
    QLabel* threadsLabel;
    
    // Performance chart
    QtCharts::QChartView* chartView;
    QtCharts::QChart* chart;
    QtCharts::QLineSeries* performanceSeries;
};

#endif // PROGRESSDASHBOARD_HPP
