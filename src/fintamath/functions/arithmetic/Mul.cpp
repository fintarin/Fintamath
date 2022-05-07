#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/core/Arithmetic.hpp"

namespace fintamath {
  std::string Mul::toString() const {
    return "*";
  }

  int Mul::getPriority() const {
    return priority;
  }

  bool Mul::equals(const Mul & /*rhs*/) const {
    return true;
  }

  MathObjectPtr Mul::operator()(const MathObject &lhs, const MathObject &rhs) const {
    if (!lhs.instanceOf<Arithmetic>() || !rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }
    return lhs.to<Arithmetic>() * rhs.to<Arithmetic>();
  }

  MathObjectPtr Mul::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 2) {
      throw std::invalid_argument("The number of arguments must be 2");
    }
    return Mul::operator()(argsVect.at(0).get(), argsVect.at(1).get());
  }
}
