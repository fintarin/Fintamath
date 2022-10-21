#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  Pow::Pow() : IOperatorCRTP(IOperator::Priority::Exponentiation) {
  }

  std::string Pow::toString() const {
    return "^";
  }

  MathObjectPtr Pow::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;

    return pow(helpers::convertMathObject(argsVect.at(0), Rational())->to<Rational>(),
               helpers::convertMathObject(argsVect.at(1), Rational())->to<Rational>(), defaultPrecision)
        .simplify();
  }
}
