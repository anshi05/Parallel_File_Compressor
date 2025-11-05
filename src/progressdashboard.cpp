#include "progressdashboard.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

using namespace QtCharts;

ProgressDashboard::ProgressDashboard(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

void ProgressDashboard::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QGroupBox* statsGroup = new QGroupBox("Compression Statistics", this);
    QGridLayout* gridLayout = new QGridLayout(statsGroup);
    
    gridLayout->addWidget(new QLabel("File Size:"), 0, 0);
    filesizeLabel = new QLabel("N/A");
    gridLayout->addWidget(filesizeLabel, 0, 1);
    
    gridLayout->addWidget(new QLabel("Compression Ratio:"), 0, 2);
    compressionRatioLabel = new QLabel("N/A");
    gridLayout->addWidget(compressionRatioLabel, 0, 3);
    
    gridLayout->addWidget(new QLabel("Speedup:"), 1, 0);
    speedupLabel = new QLabel("N/A");
    gridLayout->addWidget(speedupLabel, 1, 1);
    
    gridLayout->addWidget(new QLabel("Time Elapsed:"), 1, 2);
    timeLabel = new QLabel("N/A");
    gridLayout->addWidget(timeLabel, 1, 3);
    
    gridLayout->addWidget(new QLabel("Threads Used:"), 2, 0);
    threadsLabel = new QLabel("N/A");
    gridLayout->addWidget(threadsLabel, 2, 1);
    
    mainLayout->addWidget(statsGroup);
    
    chart = new QChart();
    chart->setTitle("Performance Comparison");
    performanceSeries = new QLineSeries();
    performanceSeries->setName("Compression Time");
    chart->addSeries(performanceSeries);
    
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
}

void ProgressDashboard::updateStats(uint64_t originalSize, uint64_t compressedSize, 
                                    double compressionRatio, double speedup, double timeMs) {
    filesizeLabel->setText(QString("%1 MB -> %2 MB")
                          .arg(originalSize / (1024.0 * 1024.0), 0, 'f', 2)
                          .arg(compressedSize / (1024.0 * 1024.0), 0, 'f', 2));
    
    compressionRatioLabel->setText(QString("%1%").arg(compressionRatio, 0, 'f', 2));
    speedupLabel->setText(QString("%1x").arg(speedup, 0, 'f', 2));
    timeLabel->setText(QString("%1 ms").arg(timeMs, 0, 'f', 2));
}

void ProgressDashboard::updatePerformanceGraph(double sequentialTime, double parallelTime) {
    performanceSeries->append(sequentialTime, 1);
    performanceSeries->append(parallelTime, 2);
}

void ProgressDashboard::reset() {
    filesizeLabel->setText("N/A");
    compressionRatioLabel->setText("N/A");
    speedupLabel->setText("N/A");
    timeLabel->setText("N/A");
    threadsLabel->setText("N/A");
    performanceSeries->clear();
}
