#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

class MouseFilter;
class QTimer;
class QTimeLine;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void closeEvent(QCloseEvent *event) override;

private slots:
  void startSlot_();
  void stopSlot_();
  void clickSlot_();
  void updateNumberSlot_();

private:
  struct Settings
  {
    int maxNumber;
    int periodSec;
  };

  void connect_();
  void loadSettings_();
  void saveSettings_();
  void resetTimeLine_();
  void resetRightCounter_();
  void resetWrongCounter_();
  void reset_();
  void incRightCounter_();
  void incWrongCounter_();
  void generateNumber_();

  inline static int minNumber = 0;
  inline static int maxNumber = 99;
  inline static int defaultMaxNumber = 10;
  inline static int minPeriodSec = 1;
  inline static int maxPeriodSec = 20;
  inline static int defaultPeriodSec = 2;
  inline static int factorForMsec = 1000;

  Ui::MainWindow *ui;
  Settings settings_;
  QTimer *timer_;
  QTimeLine *timeLine_;
  MouseFilter *mouseFilter_;
  unsigned int rightCounter_;
  unsigned int wrongCounter_;
  unsigned int clickCounter_;
  int nextNumber_;
};
#endif // MAINWINDOW_H_

