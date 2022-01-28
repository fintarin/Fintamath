#ifndef CALCULATORHANDLER_HPP
#define CALCULATORHANDLER_HPP

#include <QObject>
#include <QString>

class CalculatorHandler : public QObject {
  Q_OBJECT

private slots:
  void onStartCalculation(const QString &str);
  void onTerminateCalculation();

signals:
  void solved(const QString &str);
  void terminateCalculation();
};

#endif // CALCULATORHANDLER_HPP
