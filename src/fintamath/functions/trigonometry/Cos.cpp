#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Cos::toString() const {
    return "cos";
  }

  MathObjectPtr Cos::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(cos(newRhs->to<Rational>(), defaultPrecision));
  }

  MathObjectPtr Cos::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Cos::operator()(argsVect.at(0).get());
  }
}
