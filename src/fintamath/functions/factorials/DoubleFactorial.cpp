#include "fintamath/functions/factorials/DoubleFactorial.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string DoubleFactorial::toString() const {
    return "!!";
  }

  MathObjectPtr DoubleFactorial::operator()(const MathObject &rhs) const {
    if (!rhs.is<Integer>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(doubleFactorial(newRhs->to<Rational>()));
  }

  MathObjectPtr DoubleFactorial::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return DoubleFactorial::operator()(argsVect.at(0).get());
  }
}
