#include "fintamath/math_objects/nodes/terms/constants/MathConstant.hpp"

#include <iosfwd>
#include <stdexcept>
#include <string>

#include "fintamath/math_objects/relations/functions/NamespaceFunctions.hpp"

MathConstant::MathConstant(const std::string &strConst) {
  if (!types::isConstant(strConst)) {
    throw std::invalid_argument("Constant invalid input");
  }
  name = strConst;
}

Rational MathConstant::toRational(int64_t precision) const {
  if (name == "e") {
    return functions::getE(precision);
  }
  if (name == "pi") {
    return functions::getPi(precision);
  }
  throw std::invalid_argument("Constant invalid input");
}

std::string MathConstant::toString() const {
  return name;
}

std::string MathConstant::getTypeName() const {
  return "Constant";
}

namespace types {
bool isConstant(const std::string_view &str) {
  if (str == "e") {
    return true;
  }
  if (str == "pi") {
    return true;
  }
  return false;
}
} // namespace types
