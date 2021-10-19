#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

#include "calculator/Parser.hpp"
#include "calculator/Solver.hpp"
#include "numbers/Fraction.hpp"

constexpr int64_t PRECISION = 36;
constexpr int64_t ROUND_CONST = 9;
constexpr int64_t PRECISION_OF_CONSTANTS = PRECISION + ROUND_CONST * 2;

class Calculator {
public:
  static Fraction &getE();
  static Fraction &getPi();

  std::string calculate(const std::string &);

private:
  Solver solver;

  static Fraction E;  // NOLINT
  static Fraction PI; // NOLINT
};

#endif // CALCULATOR_HPP