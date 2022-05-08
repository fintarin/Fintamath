#include "fintamath/literals/Constant.hpp"

#include <stdexcept>

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  bool isConstant(const std::string &str);

  Constant::Constant(const std::string &str) {
    parse(str);
  }

  Rational Constant::toRational(int64_t precision) const {
    if (name == "e") {
      return getE(precision);
    }
    if (name == "pi") {
      return getPi(precision);
    }
    throw std::invalid_argument("Constant invalid input");
  }

  std::string Constant::toString() const {
    return name;
  }

  void Constant::parse(const std::string &str) {
    if (!isConstant(str)) {
      throw std::invalid_argument("Constant invalid input");
    }
    name = str;
  }

  bool isConstant(const std::string &str) {
    if (str == "e") {
      return true;
    }
    if (str == "pi") {
      return true;
    }
    return false;
  }
}
