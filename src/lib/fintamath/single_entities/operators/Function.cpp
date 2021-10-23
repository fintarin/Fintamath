#include "single_entities/operators/Function.hpp"

#include <iosfwd>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

Function::Function(const string &strFunc) {
  if (!types::isFunction(strFunc)) {
    throw invalid_argument("Function invalid input");
  }
  name = strFunc;
}

Rational Function::solve(const Rational &rhs, int64_t precision) const {
  if (name == "sqrt") {
    return functions::sqrt(rhs, precision);
  }
  if (name == "exp") {
    return functions::exp(rhs, precision);
  }
  if (name == "ln") {
    return functions::ln(rhs, precision);
  }
  if (name == "lb") {
    return functions::lb(rhs, precision);
  }
  if (name == "lg") {
    return functions::lg(rhs, precision);
  }
  if (name == "sin") {
    return functions::sin(rhs, precision);
  }
  if (name == "cos") {
    return functions::cos(rhs, precision);
  }
  if (name == "tan") {
    return functions::tan(rhs, precision);
  }
  if (name == "cot") {
    return functions::cot(rhs, precision);
  }
  if (name == "asin") {
    return functions::asin(rhs, precision);
  }
  if (name == "acos") {
    return functions::acos(rhs, precision);
  }
  if (name == "atan") {
    return functions::atan(rhs, precision);
  }
  if (name == "acot") {
    return functions::acot(rhs, precision);
  }
  if (name == "abs") {
    return functions::abs(rhs);
  }
  if (name == "!") {
    return functions::factorial(rhs);
  }
  if (name == "!!") {
    return functions::doubleFactorial(rhs);
  }
  throw invalid_argument("Function invalid input");
}

Rational Function::solve(const Rational &lhs, const Rational &rhs, int64_t precision) const {
  if (name == "log") {
    return functions::log(lhs, rhs, precision);
  }
  throw invalid_argument("Function invalid input");
}

string Function::getTypeName() const {
  return "Function";
}

string Function::toString() const {
  return name;
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
