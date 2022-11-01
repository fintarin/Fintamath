#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Cos::toString() const {
    return "cos";
  }

  std::string Cos::getClassName() const {
    return "Cos";
  }

  MathObjectPtr Cos::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return cos(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
