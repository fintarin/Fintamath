#include "fintamath/functions/other/Abs.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Abs::toString() const {
    return "abs";
  }

  MathObjectPtr Abs::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return abs(meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>()).simplify();
  }

  static const bool isDefined = Function::addParser<Abs>();
}
