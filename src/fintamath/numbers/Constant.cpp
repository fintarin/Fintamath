#include "numbers/Constant.hpp"

#include <string>

#include "calculator/Calculator.hpp"
#include "calculator/ExceptionClasses.hpp"
#include "operators/NamespaceFunctions.hpp"

using namespace std;

Constant::Constant(const Constant &other) {
  this->constant = other.constant;
}

Constant::Constant(const string &inStr) {
  if (!isType::isConstant(inStr)) {
    throw IncorrectInput("Constant");
  }
  this->constant = inStr;
}

Constant &Constant::operator=(const Constant &other) {
  this->constant = other.constant;
  return *this;
}

namespace isType {
bool isConstant(const string &inStr) {
  if (inStr == "e") {
    return true;
  }
  if (inStr == "pi") {
    return true;
  }
  return false;
}
} // namespace isType

Fraction Constant::toFraction() const {
  if (this->constant == "e") {
    return functions::getE(PRECISION_OF_CONSTANTS);
  }
  if (this->constant == "pi") {
    return functions::getPi(PRECISION_OF_CONSTANTS);
  }
  throw IncorrectInput("Constant");
}

string Constant::toString() const {
  return this->toFraction().toString(PRECISION + ROUND_CONST / 2);
}

string Constant::getTypeName() const {
  return "Constant";
}
