// #include "homepage.h"
// #include "ui_homepage.h"
// // #include "mainwindow.h"
// HomePage::HomePage(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::HomePage), /*main(new MainWindow(this)),*/ ctrl(new Control(this))
// {
//     ui->setupUi(this);
//     connect(ui->returnToMain, &QPushButton::clicked, this, &HomePage::returnToHome);
//     connect(ui->Control, &QPushButton::clicked, this, &HomePage::goToControl);
//     /////////////////////////////////////////
//     mVoltageGauge = new QcGaugeWidget;
//     mVoltageGauge->addBackground(99);
//     QcBackgroundItem *bkg1 = mVoltageGauge->addBackground(92);
//     bkg1->clearrColors();
//     bkg1->addColor(0.1,Qt::black);
//     bkg1->addColor(1.0,Qt::white);

//     QcBackgroundItem *bkg2 = mVoltageGauge->addBackground(88);
//     bkg2->clearrColors();
//     bkg2->addColor(0.1,Qt::gray);
//     bkg2->addColor(1.0,Qt::darkGray);

//     auto ii = mVoltageGauge->addDegrees(65);
//     ii->setValueRange(0,280);
//     ii->setStep(10);
//     mVoltageGauge->update();

//     ii = mVoltageGauge->addDegrees(70);
//     ii->setValueRange(0,280);
//     ii->setStep(20);
//     mVoltageGauge->update();

//     auto Item = mVoltageGauge->addValues(80);
//     Item->setValueRange(0, 280); // Set minimum and maximum range
//     Item->setStep(20);           // Set step size

//     // Update the gauge to apply changes
//     mVoltageGauge->update();
//     mVoltageGauge->addColorBand(50);

//     mVoltageGauge->addLabel(70)->setText("Volt");
//     QcLabelItem *lab = mVoltageGauge->addLabel(40);
//     lab->setText("0");
//     mVoltageNeedle = mVoltageGauge->addNeedle(60);
//     mVoltageNeedle->setLabel(lab);
//     mVoltageNeedle->setColor(Qt::white);
//     mVoltageNeedle->setValueRange(0,80);
//     mVoltageGauge->addBackground(7);
//     mVoltageGauge->addGlass(88);
//     ui->Volt->addWidget(mVoltageGauge);
//     ////////////////////////////////////////////////

//     mAmpereGauge = new QcGaugeWidget;
//     mAmpereGauge->addBackground(99);
//     bkg1 = mAmpereGauge->addBackground(92);
//     bkg1->clearrColors();
//     bkg1->addColor(0.1,Qt::black);
//     bkg1->addColor(1.0,Qt::white);

//     bkg2 = mAmpereGauge->addBackground(88);
//     bkg2->clearrColors();
//     bkg2->addColor(0.1,Qt::gray);
//     bkg2->addColor(1.0,Qt::darkGray);

//     ii = mAmpereGauge->addDegrees(65);
//     ii->setValueRange(0,60);
//     ii->setStep(10);
//     mAmpereGauge->update();

//     ii = mAmpereGauge->addDegrees(70);
//     ii->setValueRange(0,60);
//     ii->setStep(20);
//     mAmpereGauge->update();

//     Item = mAmpereGauge->addValues(80);
//     Item->setValueRange(0, 60); // Set minimum and maximum range
//     Item->setStep(20);           // Set step size

//     // Update the gauge to apply changes
//     mAmpereGauge->update();
//     mAmpereGauge->addColorBand(50);

//     mAmpereGauge->addLabel(70)->setText("Amp");
//     lab = mAmpereGauge->addLabel(40);
//     lab->setText("0");
//     mAmpereNeedle = mAmpereGauge->addNeedle(60);
//     mAmpereNeedle->setLabel(lab);
//     mAmpereNeedle->setColor(Qt::white);
//     mAmpereNeedle->setValueRange(0,80);
//     mAmpereGauge->addBackground(7);
//     mAmpereGauge->addGlass(88);
//     ui->Amp->addWidget(mAmpereGauge);
//     ////////////////////////////////////////////////

//     mWattGauge = new QcGaugeWidget;
//     mWattGauge->addBackground(99);
//     bkg1 = mWattGauge->addBackground(92);
//     bkg1->clearrColors();
//     bkg1->addColor(0.1,Qt::black);
//     bkg1->addColor(1.0,Qt::white);

//     bkg2 = mWattGauge->addBackground(88);
//     bkg2->clearrColors();
//     bkg2->addColor(0.1,Qt::gray);
//     bkg2->addColor(1.0,Qt::darkGray);

//     mWattGauge->addArc(55);
//     mWattGauge->addDegrees(65)->setValueRange(0,80);
//     mWattGauge->addColorBand(50);

//     mWattGauge->addValues(80)->setValueRange(0,80);

//     mWattGauge->addLabel(70)->setText("Watt");
//     lab = mWattGauge->addLabel(40);
//     lab->setText("0");
//     mWattNeedle = mWattGauge->addNeedle(60);
//     mWattNeedle->setLabel(lab);
//     mWattNeedle->setColor(Qt::white);
//     mWattNeedle->setValueRange(0,80);
//     mWattGauge->addBackground(7);
//     mWattGauge->addGlass(88);
//     ui->Watt->addWidget(mWattGauge);
//     ////////////////////////////////////////////////
// }

// HomePage::~HomePage()
// {
//     delete ui;
//     delete mVoltageGauge;
//     delete mAmpereGauge;
//     delete mWattGauge;
//     delete mVoltageNeedle;
//     delete mAmpereNeedle;
//     delete mWattNeedle;
//     // delete main;
//     delete ctrl;
//     qDebug() << "HomePage Destructor Called\n";
// }

// void HomePage::returnToHome(){
//     // if(main == nullptr){
//     //     main = new MainWindow(this);
//     // }
//     // this->close();
//     // main->show();
// }

// void HomePage::goToControl()
// {
//     if(ctrl == nullptr)
//     {
//         ctrl = new Control(this);
//     }
//     this ->close();
//     ctrl->show();
// }
