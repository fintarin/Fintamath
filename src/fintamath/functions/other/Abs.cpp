#include "fintamath/functions/other/Abs.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Abs::toString() const {
    return "abs";
  }

  MathObjectPtr Abs::operator()(const MathObject &rhs) const {
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Rhs must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(abs(newRhs->to<Rational>()));
  }

  MathObjectPtr Abs::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Abs::operator()(argsVect.at(0).get());
  }
}