#include "fintamath/functions/factorials/Factorial.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Factorial::toString() const {
    return "!";
  }

  MathObjectPtr Factorial::operator()(const MathObject &rhs) const {
    if (!rhs.is<Integer>()) {
      throw std::invalid_argument("Rhs must be Integer");
    }

    return std::make_unique<Integer>(factorial(rhs.to<Integer>()));
  }

  MathObjectPtr Factorial::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Factorial::operator()(argsVect.at(0).get());
  }
}