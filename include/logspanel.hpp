#ifndef LOGSPANEL_HPP
#define LOGSPANEL_HPP

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

class LogsPanel : public QWidget {
    Q_OBJECT
    
public:
    LogsPanel(QWidget* parent = nullptr);
    
    void addLog(const QString& message);
    void clearLogs();
    void showMetadata(const QString& metadataInfo);
    
private:
    QTextEdit* logTextEdit;
    QTextEdit* metadataTextEdit;
    QPushButton* clearLogsBtn;
    QPushButton* clearMetadataBtn;
};

#endif // LOGSPANEL_HPP
