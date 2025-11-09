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
    statsGroup = new QGroupBox("Compression Statistics", this);
    QGridLayout* statsLayout = new QGridLayout(statsGroup);

    filesizeLabel = new QLabel("N/A");
    compressionRatioLabel = new QLabel("N/A");
    speedupLabel = new QLabel("N/A");
    timeLabel = new QLabel("N/A");
    threadsLabel = new QLabel(QString::number(QThread::idealThreadCount()));

    statsLayout->addWidget(new QLabel("File Size:"), 0, 0);
    statsLayout->addWidget(filesizeLabel, 0, 1);
    ratioLabel = new QLabel("Compression Ratio:");
    statsLayout->addWidget(ratioLabel, 1, 0);
    statsLayout->addWidget(compressionRatioLabel, 1, 1);
    statsLayout->addWidget(new QLabel("Speedup:"), 2, 0);
    statsLayout->addWidget(speedupLabel, 2, 1);
    statsLayout->addWidget(new QLabel("Time (ms):"), 3, 0);
    statsLayout->addWidget(timeLabel, 3, 1);
    statsLayout->addWidget(new QLabel("Threads:"), 4, 0);
    statsLayout->addWidget(threadsLabel, 4, 1);
    
    // Benchmark-specific labels (initially hidden)
    sequentialTimeLabelText = new QLabel("Sequential Time:");
    sequentialTimeLabel = new QLabel("N/A");
    parallelTimeLabelText = new QLabel("Parallel Time:");
    parallelTimeLabel = new QLabel("N/A");
    efficiencyLabelText = new QLabel("Parallel Efficiency:");
    efficiencyLabel = new QLabel("N/A");
    
    statsLayout->addWidget(sequentialTimeLabelText, 5, 0);
    statsLayout->addWidget(sequentialTimeLabel, 5, 1);
    statsLayout->addWidget(parallelTimeLabelText, 6, 0);
    statsLayout->addWidget(parallelTimeLabel, 6, 1);
    statsLayout->addWidget(efficiencyLabelText, 7, 0);
    statsLayout->addWidget(efficiencyLabel, 7, 1);
    
    // Hide benchmark labels initially
    sequentialTimeLabelText->setVisible(false);
    sequentialTimeLabel->setVisible(false);
    parallelTimeLabelText->setVisible(false);
    parallelTimeLabel->setVisible(false);
    efficiencyLabelText->setVisible(false);
    efficiencyLabel->setVisible(false);

    statsGroup->setLayout(statsLayout);
    mainLayout->addWidget(statsGroup);

    // --- Chart section ---
    chart = new QChart();
    chart->setTitle("Performance Comparison (Sequential vs Parallel)");

    performanceSeries = new QLineSeries();
    performanceSeries->setName("Execution Time");
    chart->addSeries(performanceSeries);

    // attach axes
    QValueAxis* axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Run");
    axisX->setRange(0, 3);
    axisX->setTickCount(4);

    QValueAxis* axisY = new QValueAxis();
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Time (ms)");
    axisY->setMin(0);

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
    
    // Hide benchmark-specific labels for regular compression/decompression
    if (sequentialTimeLabelText) sequentialTimeLabelText->setVisible(false);
    if (sequentialTimeLabel) sequentialTimeLabel->setVisible(false);
    if (parallelTimeLabelText) parallelTimeLabelText->setVisible(false);
    if (parallelTimeLabel) parallelTimeLabel->setVisible(false);
    if (efficiencyLabelText) efficiencyLabelText->setVisible(false);
    if (efficiencyLabel) efficiencyLabel->setVisible(false);
    
    // Show regular time label
    if (timeLabel) timeLabel->setVisible(true);
}

void ProgressDashboard::updateBenchmarkStats(uint64_t originalSize, uint64_t compressedSize,
                                             double compressionRatio, double sequentialTime,
                                             double parallelTime, double speedup, double efficiency)
{
    // Update common stats
    filesizeLabel->setText(QString("%1 MB → %2 MB")
                           .arg(originalSize / (1024.0 * 1024.0), 0, 'f', 2)
                           .arg(compressedSize / (1024.0 * 1024.0), 0, 'f', 2));
    compressionRatioLabel->setText(QString("%1%").arg(compressionRatio, 0, 'f', 2));
    speedupLabel->setText(QString("%1x").arg(speedup, 0, 'f', 2));
    
    // Update benchmark-specific stats
    if (sequentialTimeLabel) {
        sequentialTimeLabel->setText(QString("%1 ms").arg(sequentialTime, 0, 'f', 2));
        sequentialTimeLabel->setVisible(true);
    }
    if (parallelTimeLabel) {
        parallelTimeLabel->setText(QString("%1 ms").arg(parallelTime, 0, 'f', 2));
        parallelTimeLabel->setVisible(true);
    }
    if (efficiencyLabel) {
        efficiencyLabel->setText(QString("%1%").arg(efficiency, 0, 'f', 2));
        efficiencyLabel->setVisible(true);
    }
    
    // Show benchmark label texts
    if (sequentialTimeLabelText) sequentialTimeLabelText->setVisible(true);
    if (parallelTimeLabelText) parallelTimeLabelText->setVisible(true);
    if (efficiencyLabelText) efficiencyLabelText->setVisible(true);
    
    // Hide regular time label for benchmark (we show sequential and parallel separately)
    if (timeLabel) timeLabel->setVisible(false);
}

void ProgressDashboard::updatePerformanceGraph(double sequentialTime, double parallelTime)
{
    performanceSeries->clear();
    // use 1 and 2 as x-values to represent sequential and parallel
    performanceSeries->append(1, sequentialTime);
    performanceSeries->append(2, parallelTime);
    
    // Update Y-axis range to fit the data
    QValueAxis* axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    if (axisY) {
        double maxTime = qMax(sequentialTime, parallelTime);
        axisY->setMax(maxTime * 1.2); // Add 20% padding
    }
    
    // Update chart to refresh the view
    chart->update();
    chartView->update();
}

void ProgressDashboard::setStatisticsTitle(const QString& title)
{
    if (statsGroup) {
        statsGroup->setTitle(title);
    }
}

void ProgressDashboard::setRatioLabel(const QString& label)
{
    if (ratioLabel) {
        ratioLabel->setText(label);
    }
}

void ProgressDashboard::setThreadCount(int count)
{
    if (threadsLabel) {
        threadsLabel->setText(QString::number(count));
    }
}

void ProgressDashboard::reset()
{
    filesizeLabel->setText("N/A");
    compressionRatioLabel->setText("N/A");
    speedupLabel->setText("N/A");
    timeLabel->setText("N/A");
    threadsLabel->setText(QString::number(QThread::idealThreadCount()));
    performanceSeries->clear();
    
    // Reset title and ratio label
    if (statsGroup) {
        statsGroup->setTitle("Compression Statistics");
    }
    if (ratioLabel) {
        ratioLabel->setText("Compression Ratio:");
    }
    
    // Reset and hide benchmark labels
    if (sequentialTimeLabel) {
        sequentialTimeLabel->setText("N/A");
        sequentialTimeLabel->setVisible(false);
    }
    if (parallelTimeLabel) {
        parallelTimeLabel->setText("N/A");
        parallelTimeLabel->setVisible(false);
    }
    if (efficiencyLabel) {
        efficiencyLabel->setText("N/A");
        efficiencyLabel->setVisible(false);
    }
    if (sequentialTimeLabelText) sequentialTimeLabelText->setVisible(false);
    if (parallelTimeLabelText) parallelTimeLabelText->setVisible(false);
    if (efficiencyLabelText) efficiencyLabelText->setVisible(false);
    
    // Show regular time label again
    if (timeLabel) timeLabel->setVisible(true);
}
