#include "fintamath/nodes/constants/Constant.hpp"

#include <stdexcept>

#include "fintamath/relations/functions/NamespaceFunctions.hpp"

namespace fintamath {
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
  }
}
