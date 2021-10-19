#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

#include "calculator/Parser.hpp"
#include "calculator/Solver.hpp"
#include "numbers/Fraction.hpp"

constexpr long long PRECISION = 36;
constexpr long long ROUND_CONST = 9;
constexpr long long PRECISION_OF_CONSTANTS = PRECISION + ROUND_CONST * 2;

class Calculator {
public:
  static Fraction &getE();
  static Fraction &getPi();

  std::string calculate(const std::string &);

private:
  Parser parser;
  Solver solver;

  static Fraction E;
  static Fraction PI;
};

#endif // CALCULATOR_HPP