#include "aboutdialog.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("About Parallel File Compressor");
    setModal(true);
    resize(400, 300);
    
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel("Parallel File Compressor v2.0");
    QFont font = titleLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    titleLabel->setFont(font);
    
    layout->addWidget(titleLabel);
    
    QLabel* descLabel = new QLabel(
        "<b>About:</b><br>"
        "A high-performance file compression utility using parallel processing.<br><br>"
        "<b>Features:</b><br>"
        "• Multi-threaded compression and decompression<br>"
        "• Real-time progress tracking<br>"
        "• Performance benchmarking<br>"
        "• Modern Qt 6 GUI<br><br>"
        "<b>System Info:</b><br>"
        "Qt Version: " + QString(QT_VERSION_STR) + "<br>"
        "CPU Cores: " + QString::number(QThread::idealThreadCount())
    );
    descLabel->setWordWrap(true);
    layout->addWidget(descLabel);
    
    layout->addStretch();
    
    QPushButton* closeBtn = new QPushButton("Close");
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(closeBtn);
}
