#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Exp::toString() const {
    return "exp";
  }

  MathObjectPtr Exp::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return exp(meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool isDefined = Function::addParser<Exp>();
}
