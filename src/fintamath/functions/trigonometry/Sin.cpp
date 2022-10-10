#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Sin::toString() const {
    return "sin";
  }

  MathObjectPtr Sin::operator()(const MathObject &rhs) const {
    constexpr int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Rhs must be Number");
    }

    auto newRhs = meta::convertMathObject(rhs, Rational());
    return sin(newRhs->to<Rational>(), defaultPrecision).simplify();
  }

  MathObjectPtr Sin::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Sin::operator()(argsVect.at(0).get());
  }
}