#include "single_entities/terms/literals/Constant.hpp"

#include <stdexcept>
#include <string>

#include "single_entities/operators/NamespaceFunctions.hpp"

using namespace std;

Constant::Constant(const string &strConst) {
  if (!types::isConstant(strConst)) {
    throw invalid_argument("Constant invalid input");
  }
  name = strConst;
}

Rational Constant::toRational(int64_t precision) const {
  if (name == "e") {
    return functions::getE(precision);
  }
  if (name == "pi") {
    return functions::getPi(precision);
  }
  throw invalid_argument("Constant invalid input");
}

string Constant::toString() const {
  return name;
}

string Constant::getTypeName() const {
  return "Constant";
}

namespace types {
bool isConstant(const string &str) {
  if (str == "e") {
    return true;
  }
  if (str == "pi") {
    return true;
  }
  return false;
}
} // namespace types
