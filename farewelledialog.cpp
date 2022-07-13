#include "farewelledialog.h"

#include <QApplication>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

FarewelleDialog::FarewelleDialog(const QString &title,
                                 QWidget *parent)
  : QDialog(parent)
{
  QLabel *label = new QLabel(tr("Приходите ещё."));
  QPushButton *button = new QPushButton(tr("Обязательно приду"));
  QHBoxLayout *hLayout = new QHBoxLayout;
  hLayout->addWidget(button);
  QVBoxLayout *vLayout = new QVBoxLayout;
  vLayout->addWidget(label);
  vLayout->addLayout(hLayout);
  setLayout(vLayout);
  connect(button, &QPushButton::clicked,
          this, &QDialog::accept);

  setModal(true);
  setWindowTitle(title);
  setWindowFlags(windowFlags() &
                 ~Qt::WindowCloseButtonHint &
                 ~Qt::WindowContextHelpButtonHint);
  resize(200, 70);
}
