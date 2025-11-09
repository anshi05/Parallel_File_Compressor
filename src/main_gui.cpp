#include <QApplication>
#include <QTimer>
#include "mainwindow.hpp"
#include "splashscreen.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    QPixmap pixmap(800, 600);
    pixmap.fill(Qt::white);
    CompressorSplashScreen splash(pixmap);
    splash.showMessage("Initializing Parallel File Compressor & Decompressor...");
    splash.show();
    app.processEvents();
    
    // Create main window
    MainWindow window;
    
    // Hide splash and show main window
    splash.finish(&window);
    window.show();
    
    return app.exec();
}
