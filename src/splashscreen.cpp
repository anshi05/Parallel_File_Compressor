#include "splashscreen.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>

CompressorSplashScreen::CompressorSplashScreen(const QPixmap& pixmap)
    : QSplashScreen(pixmap)
{
}

void CompressorSplashScreen::showMessage(const QString& message) {
    QSplashScreen::showMessage(message, Qt::AlignBottom | Qt::AlignCenter, Qt::white);
}
