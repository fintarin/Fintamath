#include "numbers/Constant.hpp"

#include <stdexcept>
#include <string>

#include "calculator/Calculator.hpp"
#include "operators/NamespaceFunctions.hpp"

using namespace std;

Constant::Constant(const string &inStr) {
  if (!isType::isConstant(inStr)) {
    throw invalid_argument("Constant invalid input");
  }
  this->constant = inStr;
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
  throw invalid_argument("Constant invalid input");
}

string Constant::toString() const {
  return this->toFraction().toString(PRECISION + ROUND_CONST / 2);
}

string Constant::getTypeName() const {
  return "Constant";
}
