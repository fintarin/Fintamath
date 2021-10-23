#include "single_entities/operators/Operator.hpp"

#include <regex>
#include <stdexcept>
#include <string>

#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

Operator::Operator(const string &strOper) {
  if (!types::isOperator(strOper)) {
    throw invalid_argument("Operator invalid input");
  }
  this->name = *strOper.begin();
}

Rational Operator::solve(const Rational &lhs, const Rational &rhs, int64_t precision) const {
  switch (this->name) {
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
    throw invalid_argument("Operator invalid input");
  }
}

string Operator::getTypeName() const {
  return "Operator";
}

string Operator::toString() const {
  return string(1, this->name);
}

namespace types {
bool isOperator(const string &str) {
  regex funcRegex(R"(\+|\-|\*|\/|\^)");
  return regex_search(str, funcRegex);
}
} // namespace types
