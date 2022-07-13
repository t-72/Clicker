#ifndef MOUSEFILTER_H_
#define MOUSEFILTER_H_

#include <QObject>

class QEvent;

class MouseFilter : public QObject
{
  Q_OBJECT
public:
  MouseFilter(QObject *parent = nullptr);
signals:
  void clickSignal();
private:
  bool eventFilter(QObject *, QEvent *) override;
};

#endif // MOUSEFILTER_H_
