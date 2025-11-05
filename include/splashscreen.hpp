#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP

#include <QSplashScreen>
#include <QPixmap>

class CompressorSplashScreen : public QSplashScreen {
    Q_OBJECT
    
public:
    CompressorSplashScreen(const QPixmap& pixmap = QPixmap());
    void showMessage(const QString& message);
};

#endif // SPLASHSCREEN_HPP
