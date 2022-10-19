#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Sqrt::toString() const {
    return "sqrt";
  }

  MathObjectPtr Sqrt::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return sqrt(meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool isAdded = Function::addParser<Sqrt>();
}
