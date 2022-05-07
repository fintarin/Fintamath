#include "fintamath/functions/arithmetic/Sub.hpp"

#include "fintamath/core/Arithmetic.hpp"

namespace fintamath {
  std::string Sub::toString() const {
    return "-";
  }

  int Sub::getPriority() const {
    return priority;
  }
  bool Sub::equals(const Sub & /*rhs*/) const {
    return true;
  }

  MathObjectPtr Sub::operator()(const MathObject &lhs, const MathObject &rhs) const {
    if (!lhs.instanceOf<Arithmetic>() || !rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }
    return lhs.to<Arithmetic>() - rhs.to<Arithmetic>();
  }

  MathObjectPtr Sub::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 2) {
      throw std::invalid_argument("The number of arguments must be 2");
    }
    return Sub::operator()(argsVect.at(0).get(), argsVect.at(1).get());
  }
}