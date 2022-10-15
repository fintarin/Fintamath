#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include "fintamath/core/Arithmetic.hpp"

namespace fintamath {
  std::string UnaryPlus::toString() const {
    return "+";
  }

  int UnaryPlus::getPriority() const {
    return priority;
  }

  MathObjectPtr UnaryPlus::operator()(const MathObject &rhs) const {
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Rhs must be Arithmetic");
    }
    return rhs.clone();
  }

  MathObjectPtr UnaryPlus::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return UnaryPlus::operator()(argsVect.at(0).get());
  }
}