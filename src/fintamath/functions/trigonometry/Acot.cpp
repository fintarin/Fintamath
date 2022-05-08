#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Acot::toString() const {
    return "acot";
  }

  MathObjectPtr Acot::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Rhs must be Number");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(acot(newRhs->to<Rational>(), defaultPrecision));
  }

  MathObjectPtr Acot::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Acot::operator()(argsVect.at(0).get());
  }
}