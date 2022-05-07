#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Cot::toString() const {
    return "cot";
  }

  MathObjectPtr Cot::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(cot(newRhs->to<Rational>(), defaultPrecision));
  }

  MathObjectPtr Cot::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Cot::operator()(argsVect.at(0).get());
  }
}
