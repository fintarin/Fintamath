#include "fintamath/ui/widgets/FintamathWindow.hpp"

using namespace fintamath;

FintamathMainWindow::FintamathMainWindow(QWidget *parent) : QMainWindow(parent) {
  ui->setupUi(this);

  connect(this, SIGNAL(startCalculation(const QString &)), calculatorHandler.get(),
          SLOT(onStartCalculation(const QString &)));
  connect(this, SIGNAL(terminateCalculation()), calculatorHandler.get(), SLOT(onTerminateCalculation()));
  connect(calculatorHandler.get(), SIGNAL(solved(const QString &)), this, SLOT(onSolved(const QString &)));
}

FintamathMainWindow::~FintamathMainWindow() {
  emit terminateCalculation();
}

void FintamathMainWindow::onSolved(const QString &str) const {
  ui->output->setText(str);
}

void FintamathMainWindow::on_input_textChanged() {
  emit terminateCalculation();
  if (ui->input->toPlainText().isEmpty()) {
    ui->output->clear();
    return;
  }
  ui->output->setText("Calculating...");

  QString str = ui->input->toPlainText();
  str.replace("\n", "");
  str.replace("\t", "");
  emit startCalculation(str);
}
