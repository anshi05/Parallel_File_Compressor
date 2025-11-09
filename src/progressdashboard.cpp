#include "progressdashboard.hpp"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPainter>

ProgressDashboard::ProgressDashboard(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

void ProgressDashboard::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // --- Stats group ---
    QGroupBox* statsGroup = new QGroupBox("Compression Statistics", this);
    QGridLayout* statsLayout = new QGridLayout(statsGroup);

    filesizeLabel = new QLabel("N/A");
    compressionRatioLabel = new QLabel("N/A");
    speedupLabel = new QLabel("N/A");
    timeLabel = new QLabel("N/A");
    threadsLabel = new QLabel(QString::number(QThread::idealThreadCount()));

    statsLayout->addWidget(new QLabel("File Size:"), 0, 0);
    statsLayout->addWidget(filesizeLabel, 0, 1);
    statsLayout->addWidget(new QLabel("Compression Ratio:"), 1, 0);
    statsLayout->addWidget(compressionRatioLabel, 1, 1);
    statsLayout->addWidget(new QLabel("Speedup:"), 2, 0);
    statsLayout->addWidget(speedupLabel, 2, 1);
    statsLayout->addWidget(new QLabel("Time (ms):"), 3, 0);
    statsLayout->addWidget(timeLabel, 3, 1);
    statsLayout->addWidget(new QLabel("Threads:"), 4, 0);
    statsLayout->addWidget(threadsLabel, 4, 1);

    statsGroup->setLayout(statsLayout);
    mainLayout->addWidget(statsGroup);

    // --- Chart section ---
    chart = new QChart();
    chart->setTitle("Performance Comparison");

    performanceSeries = new QLineSeries();
    performanceSeries->setName("Execution Time");
    chart->addSeries(performanceSeries);

    // attach axes
    QValueAxis* axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Run");

    QValueAxis* axisY = new QValueAxis();
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Time (ms)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    performanceSeries->attachAxis(axisX);
    performanceSeries->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}

void ProgressDashboard::updateStats(uint64_t originalSize, uint64_t compressedSize,
                                    double compressionRatio, double speedup, double timeMs)
{
    filesizeLabel->setText(QString("%1 MB → %2 MB")
                           .arg(originalSize / (1024.0 * 1024.0), 0, 'f', 2)
                           .arg(compressedSize / (1024.0 * 1024.0), 0, 'f', 2));
    compressionRatioLabel->setText(QString("%1%").arg(compressionRatio, 0, 'f', 2));
    speedupLabel->setText(QString("%1x").arg(speedup, 0, 'f', 2));
    timeLabel->setText(QString("%1 ms").arg(timeMs, 0, 'f', 2));
}

void ProgressDashboard::updatePerformanceGraph(double sequentialTime, double parallelTime)
{
    performanceSeries->clear();
    // use 1 and 2 as x-values to represent sequential and parallel
    performanceSeries->append(1, sequentialTime);
    performanceSeries->append(2, parallelTime);
}

void ProgressDashboard::reset()
{
    filesizeLabel->setText("N/A");
    compressionRatioLabel->setText("N/A");
    speedupLabel->setText("N/A");
    timeLabel->setText("N/A");
    threadsLabel->setText(QString::number(QThread::idealThreadCount()));
    performanceSeries->clear();
}
