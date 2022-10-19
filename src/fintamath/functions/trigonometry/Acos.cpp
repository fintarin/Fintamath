#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Acos::toString() const {
    return "acos";
  }

  MathObjectPtr Acos::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return acos(meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool isDefined = Function::addParser<Acos>();
}
