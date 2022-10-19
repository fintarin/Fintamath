#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  Percent::Percent() : OperatorCRTP(Operator::Priority::PostfixUnary) {
  }

  std::string Percent::toString() const {
    return "%";
  }

  MathObjectPtr Percent::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    constexpr int64_t percentValue = 100;
    return (meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>() / percentValue).simplify();
  }

  static const bool isDefined = Operator::addParser<Percent>();
}
