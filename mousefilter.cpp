#include "mousefilter.h"

#include <QEvent>
#include <QMouseEvent>

MouseFilter::MouseFilter(QObject *parent)
  : QObject(parent)
{}

bool MouseFilter::eventFilter(QObject *, QEvent *event)
{
  if (event->type() == QEvent::MouseButtonPress ||
      event->type() == QEvent::MouseButtonDblClick)
  {
    if (static_cast<QMouseEvent *>(event)->button() == Qt::LeftButton) {
      emit clickSignal();
      return true;
    }
  }
  return false;
}
