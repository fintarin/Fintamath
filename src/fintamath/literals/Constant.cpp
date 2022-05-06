#include "fintamath/literals/Constant.hpp"

#include <stdexcept>

#include "fintamath/functions/NamespaceFunctions.hpp"

namespace fintamath {
  Constant::Constant(const std::string &str) {
    parse(str);
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

  bool Constant::equals(const Constant &rhs) const {
    return name == rhs.name;
  }

  void Constant::parse(const std::string &str) {
    if (!types::isConstant(str)) {
      throw std::invalid_argument("Constant invalid input");
    }
    name = str;
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
  }
}
