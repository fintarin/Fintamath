#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Ln::toString() const {
    return "ln";
  }

  MathObjectPtr Ln::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return ln(meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool isAdded = Function::addParser<Ln>();
}
