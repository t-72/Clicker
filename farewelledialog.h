#ifndef FAREWELLEDIALOG_H_
#define FAREWELLEDIALOG_H_

#include <QDialog>
#include <QString>

class FarewelleDialog : public QDialog
{
  Q_OBJECT
public:
  FarewelleDialog(const QString &title,
                  QWidget *parent = nullptr);
};

#endif // FAREWELLEDIALOG_H_
