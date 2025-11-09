#include "mainwindow.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QProgressBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGroupBox>
#include "utils.hpp"
#include "aboutdialog.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , optimalThreadCount(Utils::getOptimalThreadCount())
    , compressionWorker(nullptr)
    , decompressionWorker(nullptr)
    , benchmarkWorker(nullptr)
    , compressionThread(nullptr)
    , decompressionThread(nullptr)
    , benchmarkThread(nullptr)
{
    setWindowTitle("Parallel File Compressor & Decompressor");
    setWindowIcon(QIcon(":/icons/app_icon.png"));
    resize(1200, 800);
    
    setupUI();
    createMenuBar();
    connectSignals();
}

MainWindow::~MainWindow() {
    if (compressionThread) {
        compressionThread->quit();
        compressionThread->wait();
    }
    if (decompressionThread) {
        decompressionThread->quit();
        decompressionThread->wait();
    }
    if (benchmarkThread) {
        benchmarkThread->quit();
        benchmarkThread->wait();
    }
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    QGroupBox* controlGroup = new QGroupBox("Compression Controls", this);
    QVBoxLayout* controlLayout = new QVBoxLayout(controlGroup);
    
    // File selection
    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(new QLabel("Input File:"));
    inputFileEdit = new QLineEdit();
    selectInputBtn = new QPushButton("Browse...");
    inputLayout->addWidget(inputFileEdit);
    inputLayout->addWidget(selectInputBtn);
    controlLayout->addLayout(inputLayout);
    
    QHBoxLayout* outputLayout = new QHBoxLayout();
    outputLayout->addWidget(new QLabel("Output File:"));
    outputFileEdit = new QLineEdit();
    selectOutputBtn = new QPushButton("Browse...");
    outputLayout->addWidget(outputFileEdit);
    outputLayout->addWidget(selectOutputBtn);
    controlLayout->addLayout(outputLayout);
    
    // Thread count
    QHBoxLayout* threadLayout = new QHBoxLayout();
    threadLayout->addWidget(new QLabel("Thread Count:"));
    threadCountSpinBox = new QSpinBox();
    threadCountSpinBox->setMinimum(1);
    threadCountSpinBox->setMaximum(256);
    threadCountSpinBox->setValue(optimalThreadCount);
    threadLayout->addWidget(threadCountSpinBox);
    threadLayout->addStretch();
    controlLayout->addLayout(threadLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    compressBtn = new QPushButton("Compress");
    decompressBtn = new QPushButton("Decompress");
    benchmarkBtn = new QPushButton("Benchmark");
    buttonLayout->addWidget(compressBtn);
    buttonLayout->addWidget(decompressBtn);
    buttonLayout->addWidget(benchmarkBtn);
    controlLayout->addLayout(buttonLayout);
    
    mainLayout->addWidget(controlGroup);
    
    QGroupBox* progressGroup = new QGroupBox("Progress", this);
    QVBoxLayout* progressLayout = new QVBoxLayout(progressGroup);
    statusLabel = new QLabel("Ready");
    overallProgressBar = new QProgressBar();
    overallProgressBar->setValue(0);
    progressLayout->addWidget(statusLabel);
    progressLayout->addWidget(overallProgressBar);
    mainLayout->addWidget(progressGroup);
    
    tabWidget = new QTabWidget();
    dashboard = new ProgressDashboard();
    logsPanel = new LogsPanel();
    tabWidget->addTab(dashboard, "Dashboard");
    tabWidget->addTab(logsPanel, "Logs & Metadata");
    mainLayout->addWidget(tabWidget);
    
    setCentralWidget(centralWidget);
}

void MainWindow::createMenuBar() {
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    QMenu* helpMenu = menuBar->addMenu("Help");
    QAction* aboutAction = helpMenu->addAction("About");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onShowAbout);
}

void MainWindow::connectSignals() {
    connect(selectInputBtn, &QPushButton::clicked, this, &MainWindow::onSelectInputFile);
    connect(selectOutputBtn, &QPushButton::clicked, this, &MainWindow::onSelectOutputFile);
    
    connect(compressBtn, &QPushButton::clicked, this, &MainWindow::onCompressClicked);
    connect(decompressBtn, &QPushButton::clicked, this, &MainWindow::onDecompressClicked);
    connect(benchmarkBtn, &QPushButton::clicked, this, &MainWindow::onBenchmarkClicked);
}

void MainWindow::onSelectInputFile() {
    QString file = QFileDialog::getOpenFileName(this, "Select Input File");
    if (!file.isEmpty()) {
        inputFileEdit->setText(file);
    }
}

void MainWindow::onSelectOutputFile() {
    QString file = QFileDialog::getSaveFileName(this, "Select Output File");
    if (!file.isEmpty()) {
        outputFileEdit->setText(file);
    }
}

void MainWindow::onCompressClicked() {
    if (inputFileEdit->text().isEmpty() || outputFileEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please select both input and output files.");
        return;
    }
    
    if (!compressionThread) {
        compressionThread = new QThread();
        compressionWorker = new CompressionWorker();
        compressionWorker->moveToThread(compressionThread);
        
        connect(compressionThread, &QThread::finished, compressionWorker, &QObject::deleteLater);
        connect(this, &MainWindow::destroyed, compressionThread, &QThread::quit);
        connect(compressionWorker, &CompressionWorker::progressUpdated, 
                this, &MainWindow::onCompressionProgress);
        connect(compressionWorker, &CompressionWorker::compressionFinished,
                this, &MainWindow::onCompressionFinished);
        connect(compressionWorker, &CompressionWorker::errorOccurred,
                this, &MainWindow::onWorkerError);
        
        compressionThread->start();
    }
    
    compressBtn->setEnabled(false);
    statusLabel->setText("Compressing...");
    logsPanel->addLog("Starting compression of " + inputFileEdit->text());
    
    QMetaObject::invokeMethod(compressionWorker, "compress", Qt::QueuedConnection,
                            Q_ARG(QString, inputFileEdit->text()),
                            Q_ARG(QString, outputFileEdit->text()),
                            Q_ARG(int, threadCountSpinBox->value()));
}

void MainWindow::onCompressionProgress(int percentage, const QString& status) {
    overallProgressBar->setValue(percentage);
    statusLabel->setText(status);
    logsPanel->addLog(status);
}

void MainWindow::onCompressionFinished(bool success, const QString& message, 
                                       uint64_t originalSize, uint64_t compressedSize, 
                                       double timeMs) {
    compressBtn->setEnabled(true);
    
    if (success) {
        double compressionRatio = 0.0;
        if (originalSize > 0) {
            compressionRatio = (1.0 - static_cast<double>(compressedSize) / originalSize) * 100.0;
        }
        dashboard->updateStats(originalSize, compressedSize, compressionRatio, 0.0, timeMs);
        statusLabel->setText("Compression completed successfully!");
        logsPanel->addLog(message);
        overallProgressBar->setValue(100);
        QMessageBox::information(this, "Success", message);
    } else {
        statusLabel->setText("Compression failed!");
        logsPanel->addLog("Error: " + message);
        overallProgressBar->setValue(0);
        QMessageBox::critical(this, "Error", message);
    }
}

void MainWindow::onDecompressClicked() {
    if (inputFileEdit->text().isEmpty() || outputFileEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please select both input and output files.");
        return;
    }
    
    if (!decompressionThread) {
        decompressionThread = new QThread();
        decompressionWorker = new DecompressionWorker();
        decompressionWorker->moveToThread(decompressionThread);
        
        connect(decompressionThread, &QThread::finished, decompressionWorker, &QObject::deleteLater);
        connect(decompressionWorker, &DecompressionWorker::progressUpdated,
                this, &MainWindow::onDecompressionProgress);
        connect(decompressionWorker, &DecompressionWorker::decompressionFinished,
                this, &MainWindow::onDecompressionFinished);
        connect(decompressionWorker, &DecompressionWorker::errorOccurred,
                this, &MainWindow::onWorkerError);
        
        decompressionThread->start();
    }
    
    decompressBtn->setEnabled(false);
    statusLabel->setText("Decompressing...");
    logsPanel->addLog("Starting decompression of " + inputFileEdit->text());
    
    QMetaObject::invokeMethod(decompressionWorker, "decompress", Qt::QueuedConnection,
                            Q_ARG(QString, inputFileEdit->text()),
                            Q_ARG(QString, outputFileEdit->text()),
                            Q_ARG(int, threadCountSpinBox->value()));
}

void MainWindow::onDecompressionProgress(int percentage, const QString& status) {
    overallProgressBar->setValue(percentage);
    statusLabel->setText(status);
    logsPanel->addLog(status);
}

void MainWindow::onDecompressionFinished(bool success, const QString& message, double timeMs) {
    decompressBtn->setEnabled(true);
    statusLabel->setText(success ? "Decompression completed!" : "Decompression failed!");
    logsPanel->addLog(message);
    if (success) {
        QMessageBox::information(this, "Success", message);
    } else {
        QMessageBox::critical(this, "Error", message);
    }
    overallProgressBar->setValue(0);
}

void MainWindow::onBenchmarkClicked() {
    if (inputFileEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please select an input file.");
        return;
    }
    
    if (!benchmarkThread) {
        benchmarkThread = new QThread();
        benchmarkWorker = new BenchmarkWorker();
        benchmarkWorker->moveToThread(benchmarkThread);
        
        connect(benchmarkThread, &QThread::finished, benchmarkWorker, &QObject::deleteLater);
        connect(benchmarkWorker, &BenchmarkWorker::progressUpdated,
                this, &MainWindow::onBenchmarkProgress);
        connect(benchmarkWorker, &BenchmarkWorker::benchmarkFinished,
                this, &MainWindow::onBenchmarkFinished);
        connect(benchmarkWorker, &BenchmarkWorker::errorOccurred,
                this, &MainWindow::onWorkerError);
        
        benchmarkThread->start();
    }
    
    benchmarkBtn->setEnabled(false);
    statusLabel->setText("Running benchmark...");
    logsPanel->addLog("Starting benchmark on " + inputFileEdit->text());
    
    QMetaObject::invokeMethod(benchmarkWorker, "runBenchmark", Qt::QueuedConnection,
                            Q_ARG(QString, inputFileEdit->text()),
                            Q_ARG(int, threadCountSpinBox->value()));
}

void MainWindow::onBenchmarkProgress(const QString& status) {
    statusLabel->setText(status);
    logsPanel->addLog(status);
}

void MainWindow::onBenchmarkFinished(double sequentialTime, double parallelTime, 
                                    double speedup, double efficiency,
                                    uint64_t originalSize, uint64_t compressedSize) {
    benchmarkBtn->setEnabled(true);
    
    // Update performance graph
    dashboard->updatePerformanceGraph(sequentialTime, parallelTime);
    
    // Update dashboard stats with benchmark results
    double compressionRatio = (1.0 - static_cast<double>(compressedSize) / originalSize) * 100.0;
    dashboard->updateStats(originalSize, compressedSize, compressionRatio, speedup, parallelTime);
    
    statusLabel->setText("Benchmark completed!");
    logsPanel->addLog(QString("Speedup: %1x, Efficiency: %2%")
                     .arg(speedup, 0, 'f', 2)
                     .arg(efficiency, 0, 'f', 2));
    overallProgressBar->setValue(100);
}

void MainWindow::onWorkerError(const QString& error) {
    statusLabel->setText("Error occurred!");
    logsPanel->addLog("ERROR: " + error);
    QMessageBox::critical(this, "Error", error);
    overallProgressBar->setValue(0);
}

void MainWindow::onShowAbout() {
    AboutDialog dialog(this);
    dialog.exec();
}
