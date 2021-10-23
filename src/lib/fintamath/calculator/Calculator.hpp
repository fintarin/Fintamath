#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

#include "calculator/Solver.hpp"

class Calculator {
public:
  std::string calculate(const std::string &);
  int64_t getPrecision();
  void setPrecision(int64_t);

private:
  Solver solver;

  void toFloatingPoint(std::string &);
};

#endif // CALCULATOR_HPP