#include <QApplication>

#include "widgets/FintamathWindow.hpp"

using namespace fintamath;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  FintamathMainWindow mainWindow;
  mainWindow.show();
  QApplication::exec();
}
