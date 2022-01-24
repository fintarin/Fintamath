#include "single_entities/terms/literals/Constant.hpp"

#include <iosfwd>
#include <stdexcept>
#include <string>

#include "single_entities/operators/NamespaceFunctions.hpp"

Constant::Constant(const std::string &strConst) {
  if (!types::isConstant(strConst)) {
    throw std::invalid_argument("Constant invalid input");
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
  throw std::invalid_argument("Constant invalid input");
}

std::string Constant::toString() const {
  return name;
}

std::string Constant::getTypeName() const {
  return "Constant";
}

namespace types {
bool isConstant(const std::string &str) {
  if (str == "e") {
    return true;
  }
  if (str == "pi") {
    return true;
  }
  return false;
}
} // namespace types
