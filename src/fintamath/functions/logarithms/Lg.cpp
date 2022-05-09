#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Lg::toString() const {
    return "lg";
  }

  MathObjectPtr Lg::operator()(const MathObject &rhs) const {
    constexpr int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Rhs must be Arithmetic");
    }
    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return lg(newRhs->to<Rational>(), defaultPrecision).simplify();
  }

  MathObjectPtr Lg::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Lg::operator()(argsVect.at(0).get());
  }
}