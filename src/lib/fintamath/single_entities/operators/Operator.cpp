#include "single_entities/operators/Operator.hpp"

#include <stdexcept>
#include <string>

#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

Operator::Operator(const string &inStr) {
  if (!types::isOperator(inStr)) {
    throw invalid_argument("Operator invalid input");
  }
  this->oper = *inStr.begin();
}

namespace types {
bool isOperator(const string &inStr) {
  if (inStr.size() != 1) {
    return false;
  }
  if (*inStr.begin() == '+') {
    return true;
  }
  if (*inStr.begin() == '-') {
    return true;
  }
  if (*inStr.begin() == '*') {
    return true;
  }
  if (*inStr.begin() == '/') {
    return true;
  }
  if (*inStr.begin() == '^') {
    return true;
  }
  if (*inStr.begin() == '=') {
    return true;
  }
  return false;
}
} // namespace types

bool Operator::isEqualSign() const {
  return this->oper == '=';
}

Rational Operator::solve(const Rational &thisNumber, const Rational &otherNumber, int64_t precision) const {
  switch (this->oper) {
  case '+':
    return thisNumber + otherNumber;
  case '-':
    return thisNumber - otherNumber;
  case '*':
    return thisNumber * otherNumber;
  case '/':
    return thisNumber / otherNumber;
  case '^':
    return functions::pow(thisNumber, otherNumber, precision);
  }
  throw invalid_argument("Operator invalid input");
}

string Operator::getTypeName() const {
  return "Operator";
}

string Operator::toString() const {
  return {this->oper};
}
