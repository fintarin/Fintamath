#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Cos::toString() const {
    return "cos";
  }

  MathObjectPtr Cos::operator()(const MathObject &rhs) const {
    constexpr int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Rhs must be Number");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return cos(newRhs->to<Rational>(), defaultPrecision).simplify();
  }

  MathObjectPtr Cos::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Cos::operator()(argsVect.at(0).get());
  }
}
