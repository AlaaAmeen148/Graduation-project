#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <thread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    // std::thread MqttThread(&MainWindow::MqttTask, &w);
    // std::thread InternetThread(&MainWindow::internetCheck, &w);
    // // Get the primary screen's size
    // QScreen *screen = QGuiApplication::primaryScreen();
    // QRect screenGeometry = screen->availableGeometry();
    // int screenWidth = screenGeometry.width();
    // int screenHeight = screenGeometry.height();

    // // Set window size as a percentage of screen size
    // w.resize(screenWidth * 0.8, screenHeight * 0.8); // 80% of width and height
    // w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();
    // MqttThread.join();
    // InternetThread.join();
    return a.exec();
}
