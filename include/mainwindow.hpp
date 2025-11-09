#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QProgressBar>
#include <QLabel>
#include <QTabWidget>
#include <QThread>
#include <memory>
#include "compressionworker.hpp"
#include "decompressionworker.hpp"
#include "benchmarkworker.hpp"
#include "progressdashboard.hpp"
#include "logspanel.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    
private slots:
    void onCompressClicked();
    void onDecompressClicked();
    void onBenchmarkClicked();
    void onSelectInputFile();
    void onSelectOutputFile();
    void onCompressionProgress(int percentage, const QString& status);
    void onCompressionFinished(bool success, const QString& message, 
                               uint64_t originalSize, uint64_t compressedSize, double timeMs);
    void onDecompressionProgress(int percentage, const QString& status);
    void onDecompressionFinished(bool success, const QString& message, double timeMs);
    void onBenchmarkProgress(const QString& status);
    void onBenchmarkFinished(double sequentialTime, double parallelTime, 
                           double speedup, double efficiency, 
                           uint64_t originalSize, uint64_t compressedSize);
    void onWorkerError(const QString& error);
    void onShowAbout();
    
private:
    void setupUI();
    void createMenuBar();
    void connectSignals();
    
    // UI Components
    QWidget* centralWidget;
    QTabWidget* tabWidget;
    
    // Control Panel
    QLineEdit* inputFileEdit;
    QLineEdit* outputFileEdit;
    QPushButton* selectInputBtn;
    QPushButton* selectOutputBtn;
    QSpinBox* threadCountSpinBox;
    QPushButton* compressBtn;
    QPushButton* decompressBtn;
    QPushButton* benchmarkBtn;
    
    // Progress and Status
    QProgressBar* overallProgressBar;
    QLabel* statusLabel;
    
    // Dashboard and Logs
    ProgressDashboard* dashboard;
    LogsPanel* logsPanel;
    
    // Workers and threads
    CompressionWorker* compressionWorker;
    DecompressionWorker* decompressionWorker;
    BenchmarkWorker* benchmarkWorker;
    
    QThread* compressionThread;
    QThread* decompressionThread;
    QThread* benchmarkThread;
    
    int optimalThreadCount;
};

#endif // MAINWINDOW_HPP
