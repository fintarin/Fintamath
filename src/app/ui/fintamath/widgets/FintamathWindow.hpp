#ifndef FINTAMATHWINDOW_HPP
#define FINTAMATHWINDOW_HPP

#include <QMainWindow>

#include "ui/ui_FintamathMainWindow.h"

class FintamathMainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit FintamathMainWindow(QWidget *parent = nullptr);

private:
  QSharedPointer<Ui::FintamathMainWindow> ui = QSharedPointer<Ui::FintamathMainWindow>(new Ui::FintamathMainWindow);
};

#endif // FINTAMATHWINDOW_HPP
