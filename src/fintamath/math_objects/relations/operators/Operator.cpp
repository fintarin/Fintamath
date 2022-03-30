#include "fintamath/math_objects/relations/operators/Operator.hpp"

#include <regex>

#include "fintamath/math_objects/relations/functions/NamespaceFunctions.hpp"

namespace fintamath {
  Operator::Operator(const std::string &strOper) {
    if (!types::isOperator(strOper)) {
      throw std::invalid_argument("Operator invalid input");
    }
    name = *strOper.begin();
  }

  Rational Operator::solve(const Rational &lhs, const Rational &rhs, int64_t precision) const {
    switch (name) {
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;
    case '^':
      return functions::pow(lhs, rhs, precision);
    default:
      throw std::invalid_argument("Operator invalid input");
    }
  }

  std::string Operator::toString() const {
    return std::string(1, name);
  }

  namespace types {
    bool isOperator(const std::string &str) {
      std::regex funcRegex(R"(\+|\-|\*|\/|\^)");
      return regex_search(str, funcRegex);
    }
  }
}
