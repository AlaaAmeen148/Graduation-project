#include "mainwindow.h"
#include "common.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox> // Optional: For user confirmation
#include <QtConcurrent/QtConcurrent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pool(QThreadPool::globalInstance()), timer1(nullptr),
    mVoltageGauge(nullptr), mAmpereGauge(nullptr), mWattGauge(nullptr),
    mVoltageNeedle(nullptr), mAmpereNeedle(nullptr), mWattNeedle(nullptr), zoneObj{"Zone 1", false , false, false, false , false}{
    ui->setupUi(this);
    pool->start([this]() { this->MqttTask(); }, 4);
    pool->start([this]() { this->ActionTask(); }, 3);
    pool->start([this]() { this->internetCheck(); }, 3);
    // auto _ = QtConcurrent::run([this]() { this->MqttTask(); });
    // _ = QtConcurrent::run([this]() { this->ActionTask(); });
    // _ = QtConcurrent::run([this]() { this->internetCheck(); });
    // connect(this, &MainWindow::updateGuiSignal, this, [](const QString &message) {
    //     qDebug() << message;
    //     // Update GUI elements here
    // });
    ZonesInfo.push_back(zoneObj);

    if(ui->comboBox->currentIndex() == -1){
        ui->Device_1->setEnabled(false);
        ui->Device_2->setEnabled(false);
        ui->Device_3->setEnabled(false);
        ui->Device_4->setEnabled(false);
        ui->Device_5->setEnabled(false);
    }
    timer1 = new QTimer;
    timer1->stop();
    timer2= new QTimer;
    timer2->stop();

    layoutToGauges();
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::IndexChanged);
    connect(ui->MenuButton, &QPushButton::clicked, this,
            &MainWindow::enterMainMenu);
    connect(ui->Control, &QPushButton::clicked, this, &MainWindow::goToControl);
    connect(ui->Device_1, &QPushButton::clicked, this,
            &MainWindow::device_1_Button);
    connect(ui->Device_2, &QPushButton::clicked, this,
            &MainWindow::device_2_Button);
    connect(ui->Device_3, &QPushButton::clicked, this,
            &MainWindow::device_3_Button);
    connect(ui->Device_4, &QPushButton::clicked, this,
            &MainWindow::device_4_Button);
    connect(ui->Device_5, &QPushButton::clicked, this,
            &MainWindow::device_5_Button);
    connect(ui->returnToMain, &QPushButton::clicked, this,
            &MainWindow::returnToHome);
    connect(ui->Returntopage2, &QPushButton::clicked, this,
            &MainWindow::returnToMainDash);
    // connect(timer1, &QTimer::timeout, this, &MainWindow::internetCheck);
    // timer1->start(100);
    connect(ui->SleepButton, &QPushButton::clicked, this, &MainWindow::sleep);
    // connect(timer2, &QTimer::timeout, this, &MainWindow::MqttTask);
    // timer2->start(100);
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::~MainWindow
///
MainWindow::~MainWindow() {
    qDebug() << "MainWindow Destructor Called\n";
    running = false;
    delete ui;
    if (timer1 != nullptr) {
        delete timer1;
        timer1 = nullptr;
    }
    if (timer2 != nullptr) {
        delete timer1;
        timer1 = nullptr;
    }
    if (mVoltageGauge != nullptr) {
        delete mVoltageGauge;
        mVoltageGauge = nullptr;
    }
    if (mAmpereGauge != nullptr) {
        delete mAmpereGauge;
        mAmpereGauge = nullptr;
    }
    if (mWattGauge != nullptr) {
        delete mWattGauge;
        mWattGauge = nullptr;
    }
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::enterMainMenu
///
void MainWindow::enterMainMenu() { ui->stackedWidget->setCurrentIndex(1); }
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::internetCheck
///
void MainWindow::internetCheck() {
    while(running){
        QThread::msleep(100); // Simulate work
        QMutexLocker locker(&mutex);
        if (common::isInternetAvailable()) {
            if(!zonesData.startConnection()){
                qDebug() << "Broker Not Connected \n";
            }
            QPixmap pixmap(":/Qrc/connected.png");
            ui->InternetStatus->setPixmap(pixmap);
        } else {
            QPixmap pixmap(":/Qrc/disconnected.png");
            ui->InternetStatus->setPixmap(pixmap);
        }
    }
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::goToControl
///
void MainWindow::goToControl() {
    ui->stackedWidget->setCurrentWidget(ui->Control_Page);
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::device_1_Button
///
void MainWindow::device_1_Button() {
    std::string zone_name = ui->comboBox->currentText().toStdString();
    auto it = std::find_if(ZonesInfo.begin(), ZonesInfo.end(), [zone_name](ZoneInformation zone){
        return (zone.ZoneNum == zone_name);
    });
    if(it == ZonesInfo.end()){
        return;
    }else{
        if (!(it->Dev1_status)) {
            it->Dev1_status = true;
        } else {
            it->Dev1_status = false;
        }
    }
    ui->Device_1->setIcon(changeButtonIcon(it->Dev1_status));
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::device_2_Button
///
void MainWindow::device_2_Button() {
    std::string zone_name = ui->comboBox->currentText().toStdString();
    auto it = std::find_if(ZonesInfo.begin(), ZonesInfo.end(), [zone_name](ZoneInformation zone){
        return (zone.ZoneNum == zone_name);
    });
    if(it == ZonesInfo.end()){
        return;
    }else{
        if (!(it->Dev2_status)) {
            it->Dev2_status = true;
        } else {
            it->Dev2_status = false;
        }
    }
    ui->Device_2->setIcon(changeButtonIcon(it->Dev2_status));
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::device_3_Button
///
void MainWindow::device_3_Button() {
    std::string zone_name = ui->comboBox->currentText().toStdString();
    auto it = std::find_if(ZonesInfo.begin(), ZonesInfo.end(), [zone_name](ZoneInformation zone){
        return (zone.ZoneNum == zone_name);
    });
    if(it == ZonesInfo.end()){
        return;
    }else{
        if (!(it->Dev3_status)) {
            it->Dev3_status = true;
        } else {
            it->Dev3_status = false;
        }
    }
    ui->Device_3->setIcon(changeButtonIcon(it->Dev3_status));
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::device_4_Button
///
void MainWindow::device_4_Button() {
    std::string zone_name = ui->comboBox->currentText().toStdString();
    auto it = std::find_if(ZonesInfo.begin(), ZonesInfo.end(), [zone_name](ZoneInformation zone){
        return (zone.ZoneNum == zone_name);
    });
    if(it == ZonesInfo.end()){
        return;
    }else{
        if (!(it->Dev4_status)) {
            it->Dev4_status = true;
        } else {
            it->Dev4_status = false;
        }
    }
    ui->Device_4->setIcon(changeButtonIcon(it->Dev4_status));
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::device_5_Button
///
void MainWindow::device_5_Button() {
    std::string zone_name = ui->comboBox->currentText().toStdString();
    auto it = std::find_if(ZonesInfo.begin(), ZonesInfo.end(), [zone_name](ZoneInformation zone){
        return (zone.ZoneNum == zone_name);
    });
    if(it == ZonesInfo.end()){
        return;
    }else{
        if (!(it->Dev5_status)) {
            it->Dev5_status = true;
        } else {
            it->Dev5_status = false;
        }
    }
    ui->Device_5->setIcon(changeButtonIcon(it->Dev5_status));
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::returnToMainDash
///
void MainWindow::returnToMainDash() {
    ui->stackedWidget->setCurrentWidget(ui->Home_Page);
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::returnToHome
///
void MainWindow::returnToHome() {
    ui->stackedWidget->setCurrentWidget(ui->Main_Page);
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::sleep
///
void MainWindow::sleep() { common::execCommand("loginctl lock-session"); }
void MainWindow::IndexChanged(){
    std::string zone_name = ui->comboBox->currentText().toStdString();
    ui->ZoneLable->setText(QString::fromStdString(zone_name));
////////////////////////////////////////////////////////////////////////
    ui->Device_1->setEnabled(true);
    ui->Device_2->setEnabled(true);
    ui->Device_3->setEnabled(true);
    ui->Device_4->setEnabled(true);
    ui->Device_5->setEnabled(true);
////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::layoutToGauges
///
///
void MainWindow::layoutToGauges() {
    /////////////////////////////////////////
    mVoltageGauge = new QcGaugeWidget;
    mVoltageGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mVoltageGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1, Qt::black);
    bkg1->addColor(1.0, Qt::white);

    QcBackgroundItem *bkg2 = mVoltageGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1, Qt::gray);
    bkg2->addColor(1.0, Qt::darkGray);

    auto ii = mVoltageGauge->addDegrees(65);
    ii->setValueRange(0, 280);
    ii->setStep(10);
    mVoltageGauge->update();

    ii = mVoltageGauge->addDegrees(70);
    ii->setValueRange(0, 280);
    ii->setStep(20);
    mVoltageGauge->update();

    auto Item = mVoltageGauge->addValues(80);
    Item->setValueRange(0, 280); // Set minimum and maximum range
    Item->setStep(20);           // Set step size

    // Update the gauge to apply changes
    mVoltageGauge->update();
    mVoltageGauge->addColorBand(50);

    mVoltageGauge->addLabel(70)->setText("Volt");
    QcLabelItem *lab = mVoltageGauge->addLabel(40);
    lab->setText("0");
    mVoltageNeedle = mVoltageGauge->addNeedle(60);
    mVoltageNeedle->setLabel(lab);
    mVoltageNeedle->setColor(Qt::white);
    mVoltageNeedle->setValueRange(0, 80);
    mVoltageGauge->addBackground(7);
    mVoltageGauge->addGlass(88);
    ui->Volt->addWidget(mVoltageGauge);
    ////////////////////////////////////////////////

    mAmpereGauge = new QcGaugeWidget;
    mAmpereGauge->addBackground(99);
    bkg1 = mAmpereGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1, Qt::black);
    bkg1->addColor(1.0, Qt::white);

    bkg2 = mAmpereGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1, Qt::gray);
    bkg2->addColor(1.0, Qt::darkGray);

    ii = mAmpereGauge->addDegrees(65);
    ii->setValueRange(0, 60);
    ii->setStep(10);
    mAmpereGauge->update();

    ii = mAmpereGauge->addDegrees(70);
    ii->setValueRange(0, 60);
    ii->setStep(20);
    mAmpereGauge->update();

    Item = mAmpereGauge->addValues(80);
    Item->setValueRange(0, 60); // Set minimum and maximum range
    Item->setStep(20);          // Set step size

    // Update the gauge to apply changes
    mAmpereGauge->update();
    mAmpereGauge->addColorBand(50);

    mAmpereGauge->addLabel(70)->setText("Amp");
    lab = mAmpereGauge->addLabel(40);
    lab->setText("0");
    mAmpereNeedle = mAmpereGauge->addNeedle(60);
    mAmpereNeedle->setLabel(lab);
    mAmpereNeedle->setColor(Qt::white);
    mAmpereNeedle->setValueRange(0, 80);
    mAmpereGauge->addBackground(7);
    mAmpereGauge->addGlass(88);
    ui->Amp->addWidget(mAmpereGauge);
    ////////////////////////////////////////////////

    mWattGauge = new QcGaugeWidget;
    mWattGauge->addBackground(99);
    bkg1 = mWattGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1, Qt::black);
    bkg1->addColor(1.0, Qt::white);

    bkg2 = mWattGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1, Qt::gray);
    bkg2->addColor(1.0, Qt::darkGray);

    mWattGauge->addArc(55);
    mWattGauge->addDegrees(65)->setValueRange(0, 80);
    mWattGauge->addColorBand(50);

    mWattGauge->addValues(80)->setValueRange(0, 80);

    mWattGauge->addLabel(70)->setText("Watt");
    lab = mWattGauge->addLabel(40);
    lab->setText("0");
    mWattNeedle = mWattGauge->addNeedle(60);
    mWattNeedle->setLabel(lab);
    mWattNeedle->setColor(Qt::white);
    mWattNeedle->setValueRange(0, 80);
    mWattGauge->addBackground(7);
    mWattGauge->addGlass(88);
    ui->Watt->addWidget(mWattGauge);
    ////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::changeButtonIcon
/// \param on
/// \return
///
QIcon MainWindow::changeButtonIcon(bool on) {
    QIcon temp;
    if (on) {
        temp = QIcon(":/Qrc/on.png");
    } else {
        temp = QIcon(":/Qrc/off.png");
    }
    return temp;
}
//////////////////////////////////////////////
void MainWindow::DontKnowNow()
{
    std::string zone_name = ui->comboBox->currentText().toStdString();
    auto it = std::find_if(ZonesInfo.begin(), ZonesInfo.end(), [zone_name](ZoneInformation zone){
        return (zone.ZoneNum == zone_name);
    });
    if(it == ZonesInfo.end()){

    }else{
        ui->Device_1->setIcon(changeButtonIcon(it->Dev1_status));
        ui->Device_2->setIcon(changeButtonIcon(it->Dev2_status));
        ui->Device_3->setIcon(changeButtonIcon(it->Dev3_status));
        ui->Device_4->setIcon(changeButtonIcon(it->Dev4_status));
        ui->Device_5->setIcon(changeButtonIcon(it->Dev5_status));
    }
}
void MainWindow::MqttTask() {
    while (running) {
        QThread::msleep(10); // Simulate work
        QMutexLocker locker(&mutex);
        ZoneInformation temp = zonesData.getMessage();
        if(temp.ZoneNum == "Null"){
            return;
        }
        auto it = std::find_if(ZonesInfo.begin(), ZonesInfo.end(), [temp](ZoneInformation zone){
            return (zone.ZoneNum == temp.ZoneNum);
        });
        if(it == ZonesInfo.end()){
            return;
        }

        it->Dev1_status = temp.Dev1_status;
        it->Dev2_status = temp.Dev2_status;
        it->Dev3_status = temp.Dev3_status;
        it->Dev4_status = temp.Dev4_status;
        it->Dev5_status = temp.Dev5_status;

        ui->comboBox->setCurrentText(QString::fromStdString(it->ZoneNum));

        qDebug() << "Fetching MQTT data...";
    }
    qDebug() << "Stopped Fetching MQTT data...";
}

void MainWindow::ActionTask() {
    while (running) {
        QThread::msleep(200); // Simulate work
        QMutexLocker locker(&mutex);
        DontKnowNow();
        qDebug() << "Performing actions...";
    }
    qDebug() << "Stopped Performing actions...";
}

