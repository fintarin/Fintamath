#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Exp::toString() const {
    return "exp";
  }

  std::string Exp::getClassName() const {
    return "Exp";
  }

  MathObjectPtr Exp::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return exp(helpers::Converter::convert(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }
}
