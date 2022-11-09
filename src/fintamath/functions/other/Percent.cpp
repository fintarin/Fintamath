#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  Percent::Percent() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string Percent::toString() const {
    return "%";
  }

  std::string Percent::getClassName() const {
    return "Percent";
  }

  MathObjectPtr Percent::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t percentValue = 100;
    return (helpers::Converter::convert(argsVect.at(0), Rational())->to<Rational>() / percentValue).simplify();
  }
}
