#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Acos::toString() const {
    return "acos";
  }

  std::string Acos::getClassName() const {
    return "Acos";
  }

  MathObjectPtr Acos::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return acos(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
