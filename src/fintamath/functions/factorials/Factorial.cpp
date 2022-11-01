#include "fintamath/functions/factorials/Factorial.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  Factorial::Factorial() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string Factorial::toString() const {
    return "!";
  }

  std::string Factorial::getClassName() const {
    return "Factorial";
  }

  MathObjectPtr Factorial::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return std::make_unique<Integer>(factorial(argsVect.at(0).get().to<Integer>()));
  }
}
