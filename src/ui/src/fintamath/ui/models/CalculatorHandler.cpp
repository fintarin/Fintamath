#include "fintamath/ui/models/CalculatorHandler.hpp"

#include <QtConcurrent/QtConcurrent>

constexpr int64_t WAITING_TIME = 10;

void CalculatorHandler::onStartCalculation(const QString &str) {
  QtConcurrent::run([this, str]() {
    QProcess proc;
    connect(this, SIGNAL(terminateCalculation()), &proc, SLOT(kill()));
    proc.start(PRESENTER_BINARY, QStringList(str));

    while (!proc.waitForFinished(WAITING_TIME)) {
      QCoreApplication::processEvents();
      if (!proc.isOpen()) {
        return;
      }
    }

    QString res(proc.readAll());
    if (!res.isEmpty()) {
      emit solved(res);
    }
  });
}

void CalculatorHandler::onTerminateCalculation() {
  emit terminateCalculation();
}
