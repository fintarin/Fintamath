#include "fintamath/operators/Neg.hpp"

namespace fintamath {
  std::string Neg::toString() const {
    return "-";
  }

  int Neg::getPriority() const{
    return priority;
  }
  bool Neg::equals(const Neg & /*rhs*/) const {
    return true;
  }

  MathObjectPtr Neg::operator()(const MathObject &rhs) const {
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }
    return -rhs.to<Arithmetic>();
  }

  MathObjectPtr Neg::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Neg::operator()(argsVect.at(0).get());
  }
}