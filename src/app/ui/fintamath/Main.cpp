#include <iostream>
#include <string>

#include <QApplication>

#include "widgets/FintamathWindow.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  FintamathMainWindow mainWindow;
  mainWindow.show();
  QApplication::exec();
}
