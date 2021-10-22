#include "single_entities/operators/Function.hpp"

#include <stdexcept>
#include <string>

#include "calculator/Calculator.hpp"
#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

Function::Function(const string &inStr) {
  if (!isType::isFunction(inStr)) {
    throw invalid_argument("Function invalid input");
  }
  this->func = inStr;
}

bool isType::isFunction(const string &inStr) {
  if (inStr == "sqrt") {
    return true;
  }
  if (inStr == "exp") {
    return true;
  }
  if (inStr == "log") {
    return true;
  }
  if (inStr == "ln") {
    return true;
  }
  if (inStr == "lb") {
    return true;
  }
  if (inStr == "lg") {
    return true;
  }
  if (inStr == "sin") {
    return true;
  }
  if (inStr == "cos") {
    return true;
  }
  if (inStr == "tan") {
    return true;
  }
  if (inStr == "cot") {
    return true;
  }
  if (inStr == "asin") {
    return true;
  }
  if (inStr == "acos") {
    return true;
  }
  if (inStr == "atan") {
    return true;
  }
  if (inStr == "acot") {
    return true;
  }
  if (inStr == "abs") {
    return true;
  }
  if (inStr == "!") {
    return true;
  }
  if (inStr == "!!") {
    return true;
  }
  return false;
}

bool isType::isBinaryFunction(const string &inStr) {
  return (inStr == "log");
}

Rational Function::solve(const Rational &frac) const {
  if (this->func == "sqrt") {
    return functions::sqrt(frac, PRECISION);
  }
  if (this->func == "exp") {
    return functions::exp(frac, PRECISION);
  }
  if (this->func == "ln") {
    return functions::ln(frac, PRECISION);
  }
  if (this->func == "lb") {
    return functions::lb(frac, PRECISION);
  }
  if (this->func == "lg") {
    return functions::lg(frac, PRECISION);
  }
  if (this->func == "sin") {
    return functions::sin(frac, PRECISION);
  }
  if (this->func == "cos") {
    return functions::cos(frac, PRECISION);
  }
  if (this->func == "tan") {
    return functions::tan(frac, PRECISION);
  }
  if (this->func == "cot") {
    return functions::cot(frac, PRECISION);
  }
  if (this->func == "asin") {
    return functions::asin(frac, PRECISION);
  }
  if (this->func == "acos") {
    return functions::acos(frac, PRECISION);
  }
  if (this->func == "atan") {
    return functions::atan(frac, PRECISION);
  }
  if (this->func == "acot") {
    return functions::acot(frac, PRECISION);
  }
  if (this->func == "abs") {
    return functions::abs(frac);
  }
  if (this->func == "!") {
    return functions::factorial(frac);
  }
  if (this->func == "!!") {
    return functions::doubleFactorial(frac);
  }
  throw invalid_argument("Function invalid input");
}

Rational Function::solve(const Rational &base, const Rational &frac) const {
  if (this->func == "log") {
    return functions::log(base, frac, PRECISION);
  }
  throw invalid_argument("Function invalid input");
}

string Function::getTypeName() const {
  return "Function";
}

string Function::toString() const {
  return this->func;
}
