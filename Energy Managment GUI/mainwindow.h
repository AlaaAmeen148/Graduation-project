#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThreadPool>
#include <QMutex>

#include "qcgaugewidget.h"
#include "zones.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // void MqttTask();
    // void internetCheck();
private slots:
    void enterMainMenu();
    void goToControl();
    void internetCheck();
    void device_1_Button();
    void device_2_Button();
    void device_3_Button();
    void device_4_Button();
    void device_5_Button();
    void returnToMainDash();
    void returnToHome();
    void sleep();
    void IndexChanged();
signals:
    void updateGuiSignal(const QString &message);
private:
    Ui::MainWindow *ui;
    //////////////////////////////////////////////
    //////////////////////////////////////////////
    Zones          zonesData;
    //////////////////////////////////////////////
    QTimer         *timer1;
    QTimer         *timer2;
    //////////////////////////////////////////////
    QcGaugeWidget  *mVoltageGauge;
    QcGaugeWidget  *mAmpereGauge;
    QcGaugeWidget  *mWattGauge;
    //////////////////////////////////////////////
    QcNeedleItem   *mVoltageNeedle;
    QcNeedleItem   *mAmpereNeedle;
    QcNeedleItem   *mWattNeedle;
    //////////////////////////////////////////////
    ZoneInformation zoneObj;
    std::list<ZoneInformation> ZonesInfo;
    //////////////////////////////////////////////
    void layoutToGauges();
    QIcon changeButtonIcon(bool);
    //////////////////////////////////////////////
    void MqttTask();
    void ActionTask();
    void DontKnowNow();
    //////////////////////////////////////////////
    std::atomic<bool> running{true};
    QMutex mutex;
    QThreadPool    *pool;
};

#endif // MAINWINDOW_H
// std::map<std::string, std::map<uint8_t, bool>> ZonesInfo;
