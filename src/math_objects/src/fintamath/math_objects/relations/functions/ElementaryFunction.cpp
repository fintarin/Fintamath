#include "fintamath/math_objects/relations/functions/ElementaryFunction.hpp"

#include <regex>

#include "fintamath/math_objects/relations/functions/NamespaceFunctions.hpp"

ElementaryFunction::ElementaryFunction(const std::string &strFunc) {
  if (!types::isFunction(strFunc)) {
    throw std::invalid_argument("Function invalid input");
  }
  name = strFunc;
}

Rational ElementaryFunction::solve(const Rational &rhs, int64_t precision) const {
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
  throw std::invalid_argument("Function invalid input");
}

Rational ElementaryFunction::solve(const Rational &lhs, const Rational &rhs, int64_t precision) const {
  if (name == "log") {
    return functions::log(lhs, rhs, precision);
  }
  throw std::invalid_argument("Function invalid input");
}

std::string ElementaryFunction::toString() const {
  return name;
}

namespace types {
bool isFunction(const std::string &str) {
  std::regex funcRegex(R"(sqrt|exp|log|ln|lb|lg|sin|cos|tan|cot|asin|acos|acot|abs|!|!!)");
  return regex_search(str, funcRegex);
}

bool isBinaryFunction(const std::string_view &str) {
  return (str == "log");
}
} // namespace types
