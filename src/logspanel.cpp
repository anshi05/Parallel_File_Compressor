#include "logspanel.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QDateTime>

LogsPanel::LogsPanel(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QTabWidget* tabWidget = new QTabWidget();
    
    // Logs tab
    logTextEdit = new QTextEdit();
    logTextEdit->setReadOnly(true);
    tabWidget->addTab(logTextEdit, "Logs");
    
    // Metadata tab
    metadataTextEdit = new QTextEdit();
    metadataTextEdit->setReadOnly(true);
    tabWidget->addTab(metadataTextEdit, "Metadata");
    
    mainLayout->addWidget(tabWidget);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    clearLogsBtn = new QPushButton("Clear Logs");
    clearMetadataBtn = new QPushButton("Clear Metadata");
    connect(clearLogsBtn, &QPushButton::clicked, this, &LogsPanel::clearLogs);
    connect(clearMetadataBtn, &QPushButton::clicked, metadataTextEdit, &QTextEdit::clear);
    buttonLayout->addWidget(clearLogsBtn);
    buttonLayout->addWidget(clearMetadataBtn);
    mainLayout->addLayout(buttonLayout);
}

void LogsPanel::addLog(const QString& message) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    logTextEdit->append(QString("[%1] %2").arg(timestamp, message));
}

void LogsPanel::clearLogs() {
    logTextEdit->clear();
}

void LogsPanel::showMetadata(const QString& metadataInfo) {
    metadataTextEdit->setText(metadataInfo);
}
