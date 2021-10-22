#include <iostream>
#include <string>

#include "calculator/Calculator.hpp"

using namespace std;

int main() {
  Calculator calc;

  while (true) {
    string str;
    string res;
    cout << ">> ";
    getline(cin, str);
    cout << "<< ";

    try {
      res = calc.calculate(str);
    } catch (exception &exc) {
      res = exc.what();
    }

    cout << res << "\n\n";
  }
}
