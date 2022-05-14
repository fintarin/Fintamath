#include "fintamath/functions/logic/Eq.hpp"

#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  int Eq::getPriority() const {
    return priority;
  }

  std::string Eq::toString() const {
    return "=";
  }

  MathObjectPtr Eq::operator()(const MathObject &lhs, const MathObject &rhs) const {
    return std::make_unique<Integer>(lhs == rhs);
  }

  MathObjectPtr Eq::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 2) {
      throw std::invalid_argument("The number of arguments must be 2");
    }
    return Eq::operator()(argsVect.at(0).get(), argsVect.at(1).get());
  }
}
