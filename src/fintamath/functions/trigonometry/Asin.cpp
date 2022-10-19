#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Asin::toString() const {
    return "asin";
  }

  MathObjectPtr Asin::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return asin(meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool isDefined = Function::addParser<Asin>();
}
