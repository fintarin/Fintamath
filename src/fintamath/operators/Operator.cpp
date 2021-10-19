#include "operators/Operator.hpp"

#include <stdexcept>
#include <string>

#include "calculator/Calculator.hpp"
#include "operators/NamespaceFunctions.hpp"

using namespace std;

Operator::Operator(const Operator &inOper) {
  this->oper = inOper.oper;
}

Operator::Operator(const string &inStr) {
  if (!isType::isOperator(inStr)) {
    throw invalid_argument("Operator invalid input");
  }
  this->oper = *inStr.begin();
}

Operator &Operator::operator=(const Operator &other) {
  this->oper = other.oper;
  return *this;
}

namespace isType {
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
  throw invalid_argument("Operator invalid input");
}

string Operator::getTypeName() const {
  return "Operator";
}

string Operator::toString() const {
  return {this->oper};
}
