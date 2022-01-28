#include <iostream>
#include <stdexcept>
#include <string>

#include "fintamath/solver/Calculator.hpp"

int main(int /*argc*/, char *argv[]) {
  Calculator calc;
  try {
    std::cout << calc.calculate(std::string(argv[1]));
  } catch (const std::domain_error &exc) {
    std::cout << exc.what();
  } catch (const std::invalid_argument &) {
    std::cout << "Sorry, we cannot solve this expression";
  }
}
