#include "single_entities/terms/literals/Constant.hpp"

#include <stdexcept>
#include <string>

#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

Constant::Constant(const string &inStr) {
  if (!types::isConstant(inStr)) {
    throw invalid_argument("Constant invalid input");
  }
  this->constant = inStr;
}

namespace types {
bool isConstant(const string &inStr) {
  if (inStr == "e") {
    return true;
  }
  if (inStr == "pi") {
    return true;
  }
  return false;
}
} // namespace types

Rational Constant::toRational(int64_t precision) const {
  if (this->constant == "e") {
    return functions::getE(precision);
  }
  if (this->constant == "pi") {
    return functions::getPi(precision);
  }
  throw invalid_argument("Constant invalid input");
}

string Constant::toString() const {
  return this->constant;
}

string Constant::getTypeName() const {
  return "Constant";
}
