#include <QApplication>

#include "widgets/FintamathWindow.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  FintamathMainWindow mainWindow;
  mainWindow.show();
  QApplication::exec();
}
