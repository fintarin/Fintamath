#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Sqrt::toString() const {
    return "sqrt";
  }

  MathObjectPtr Sqrt::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Rhs must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(sqrt(newRhs->to<Rational>(), defaultPrecision));
  }

  MathObjectPtr Sqrt::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Sqrt::operator()(argsVect.at(0).get());
  }
}