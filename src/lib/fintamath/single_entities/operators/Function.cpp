#include "single_entities/operators/Function.hpp"

#include <regex>
#include <stdexcept>
#include <string>

#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

Function::Function(const string &strFunc) {
  if (!types::isFunction(strFunc)) {
    throw invalid_argument("Function invalid input");
  }
  this->name = strFunc;
}

Rational Function::solve(const Rational &rhs, int64_t precision) const {
  if (this->name == "sqrt") {
    return functions::sqrt(rhs, precision);
  }
  if (this->name == "exp") {
    return functions::exp(rhs, precision);
  }
  if (this->name == "ln") {
    return functions::ln(rhs, precision);
  }
  if (this->name == "lb") {
    return functions::lb(rhs, precision);
  }
  if (this->name == "lg") {
    return functions::lg(rhs, precision);
  }
  if (this->name == "sin") {
    return functions::sin(rhs, precision);
  }
  if (this->name == "cos") {
    return functions::cos(rhs, precision);
  }
  if (this->name == "tan") {
    return functions::tan(rhs, precision);
  }
  if (this->name == "cot") {
    return functions::cot(rhs, precision);
  }
  if (this->name == "asin") {
    return functions::asin(rhs, precision);
  }
  if (this->name == "acos") {
    return functions::acos(rhs, precision);
  }
  if (this->name == "atan") {
    return functions::atan(rhs, precision);
  }
  if (this->name == "acot") {
    return functions::acot(rhs, precision);
  }
  if (this->name == "abs") {
    return functions::abs(rhs);
  }
  if (this->name == "!") {
    return functions::factorial(rhs);
  }
  if (this->name == "!!") {
    return functions::doubleFactorial(rhs);
  }
  throw invalid_argument("Function invalid input");
}

Rational Function::solve(const Rational &lhs, const Rational &rhs, int64_t precision) const {
  if (this->name == "log") {
    return functions::log(lhs, rhs, precision);
  }
  throw invalid_argument("Function invalid input");
}

string Function::getTypeName() const {
  return "Function";
}

string Function::toString() const {
  return this->name;
}

namespace types {
bool isFunction(const string &str) {
  regex funcRegex(R"(sqrt|exp|log|ln|lb|lg|sin|cos|tan|cot|asin|acos|acot|abs|!|!!)");
  return regex_search(str, funcRegex);
}

bool isBinaryFunction(const string &str) {
  return (str == "log");
}
} // namespace types
