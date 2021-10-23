#include <iostream>
#include <stdexcept>
#include <string>

#include "calculator/Calculator.hpp"

using namespace std;

int main(int /*argc*/, char *argv[]) {
  Calculator calc;
  try {
    cout << calc.calculate(string(argv[1])); // NOLINT
  } catch (const domain_error &exc) {
    cout << exc.what();
  } catch (const invalid_argument &) {
    cout << "Sorry, we cannot solve this expression";
  }
}
