#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/core/Arithmetic.hpp"

namespace fintamath {
  std::string Div::toString() const {
    return "/";
  }

  int Div::getPriority() const {
    return priority;
  }

  MathObjectPtr Div::operator()(const MathObject &lhs, const MathObject &rhs) const {
    if (!lhs.instanceOf<Arithmetic>() || !rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Lhs and Rhs must be Arithmetic");
    }
    return lhs.to<Arithmetic>() / rhs.to<Arithmetic>();
  }

  MathObjectPtr Div::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 2) {
      throw std::invalid_argument("The number of arguments must be 2");
    }
    return Div::operator()(argsVect.at(0).get(), argsVect.at(1).get());
  }
}
