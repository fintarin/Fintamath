#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Sqrt::toString() const {
    return "sqrt";
  }

  std::string Sqrt::getClassName() const {
    return "Sqrt";
  }

  MathObjectPtr Sqrt::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return sqrt(helpers::Converter::convert(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
