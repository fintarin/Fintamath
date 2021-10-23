#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <cstdint>
#include <string>

#include "calculator/Solver.hpp"

class Calculator {
public:
  std::string calculate(const std::string &strExpr);

  int64_t getPrecision() const;
  void setPrecision(int64_t precision);

private:
  Solver solver;

  void toShortForm(std::string &strVal) const;
};

#endif // CALCULATOR_HPP