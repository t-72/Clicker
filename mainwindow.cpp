#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QRandomGenerator>
#include <QSettings>
#include <QSpacerItem>
#include <QString>
#include <QTimer>
#include <QTimeLine>
#include <QVBoxLayout>

#include "farewelledialog.h"
#include "mousefilter.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , timer_(new QTimer(this))
  , mouseFilter_(new MouseFilter(this))
  , rightCounter_(0)
  , wrongCounter_(0)
  , clickCounter_(0)
  , nextNumber_(0)
{
  ui->setupUi(this);
  loadSettings_();
  connect_();
}

MainWindow::~MainWindow()
{
  delete ui;
  saveSettings_();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  stopSlot_();
  FarewelleDialog dialog(windowTitle());
  dialog.exec();
  QMainWindow::closeEvent(event);
}

void MainWindow::startSlot_()
{
  if (!timer_->isActive()) {
    reset_();
    generateNumber_();
    timeLine_->start();
    timer_->start();
  }
}

void MainWindow::stopSlot_()
{
  timeLine_->stop();
  timer_->stop();
}

void MainWindow::clickSlot_()
{
  ++clickCounter_;
}

void MainWindow::updateNumberSlot_()
{
  resetTimeLine_();
  if (clickCounter_ == static_cast<unsigned int>(nextNumber_))
    incRightCounter_();
  else
    incWrongCounter_();
  generateNumber_();
}

void MainWindow::connect_()
{
  connect(ui->startButton, &QPushButton::clicked,
          this, &MainWindow::startSlot_);
  connect(ui->stopButton, &QPushButton::clicked,
          this, &MainWindow::stopSlot_);
  connect(timer_, &QTimer::timeout,
          this, &MainWindow::updateNumberSlot_);
  connect(timeLine_, &QTimeLine::frameChanged,
          ui->progressBar, &QProgressBar::setValue);
  connect(mouseFilter_, &MouseFilter::clickSignal,
          this, &MainWindow::clickSlot_);
  ui->lcdNumber->installEventFilter(mouseFilter_);

}

void MainWindow::loadSettings_()
{
  QString iniFile =
      QDir::toNativeSeparators(QApplication::applicationDirPath()) +
      QDir::separator() + "config.ini";

  QSettings qSettings(iniFile, QSettings::IniFormat);
  settings_.maxNumber = qSettings.value("max_number",
                                        defaultMaxNumber).toInt();
  settings_.periodSec = qSettings.value("period_sec",
                                        defaultPeriodSec).toInt();

  if (settings_.maxNumber < minNumber)
    settings_.maxNumber = minNumber;
  else if (settings_.maxNumber > maxNumber)
    settings_.maxNumber = maxNumber;

  if (settings_.periodSec < minPeriodSec)
    settings_.periodSec = minPeriodSec;
  else if (settings_.periodSec > maxPeriodSec)
    settings_.periodSec = maxPeriodSec;

  timer_->setInterval(factorForMsec * settings_.periodSec);
  timeLine_ = new QTimeLine(factorForMsec * settings_.periodSec, this);
  timeLine_->setFrameRange(ui->progressBar->minimum(),
                           ui->progressBar->maximum());
}

void MainWindow::saveSettings_()
{
  QString iniFile =
      QDir::toNativeSeparators(QApplication::applicationDirPath()) +
      QDir::separator() + "config.ini";

  QSettings qSettings(iniFile, QSettings::IniFormat);
  qSettings.setValue("max_number", settings_.maxNumber);
  qSettings.setValue("period_sec", settings_.periodSec);
}

void MainWindow::resetTimeLine_()
{
  timeLine_->stop();
  timeLine_->start();
}

void MainWindow::resetRightCounter_()
{
  rightCounter_ = 0;
  ui->labelRight->setText(QString::number(rightCounter_));
}

void MainWindow::resetWrongCounter_()
{
  wrongCounter_ = 0;
  ui->labelWrong->setText(QString::number(wrongCounter_));
}

void MainWindow::reset_()
{
  resetRightCounter_();
  resetWrongCounter_();
  clickCounter_ = 0;
}

void MainWindow::incRightCounter_()
{
  ++rightCounter_;
  ui->labelRight->setText(QString::number(rightCounter_));
}

void MainWindow::incWrongCounter_()
{
  ++wrongCounter_;
  ui->labelWrong->setText(QString::number(wrongCounter_));
}


void MainWindow::generateNumber_()
{
  clickCounter_ = 0;
  nextNumber_ = QRandomGenerator::global()
      ->bounded(minNumber, settings_.maxNumber);
  ui->lcdNumber->display(nextNumber_);
}
