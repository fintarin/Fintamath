#include "operators/Operator.hpp"

#include <string>

#include "calculator/Calculator.hpp"
#include "calculator/ExceptionClasses.hpp"
#include "operators/NamespaceFunctions.hpp"

Operator::Operator(const Operator &inOper) {
  this->oper = inOper.oper;
}

Operator::Operator(const std::string &inStr) {
  if (!isType::isOperator(inStr)) {
    throw IncorrectInput("Operator");
  }
  this->oper = *inStr.begin();
}

Operator &Operator::operator=(const Operator &other) {
  this->oper = other.oper;
  return *this;
}

namespace isType {
bool isOperator(const std::string &inStr) {
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
} // namespace isType

bool Operator::isEqualSign() const {
  return this->oper == '=';
}

Fraction Operator::solve(const Fraction &thisNumber, const Fraction &otherNumber) const {
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
    return functions::pow(thisNumber, otherNumber, PRECISION);
  }
  throw IncorrectInput("Operator");
}

std::string Operator::getTypeName() const {
  return "Operator";
}

std::string Operator::toString() const {
  return {this->oper};
}
