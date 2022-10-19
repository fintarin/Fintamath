#include "fintamath/functions/factorials/Factorial.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  Factorial::Factorial() : OperatorCRTP(Operator::Priority::PostfixUnary) {
  }

  std::string Factorial::toString() const {
    return "!";
  }

  MathObjectPtr Factorial::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return std::make_unique<Integer>(factorial(argsVect.at(0).get().to<Integer>()));
  }

  static const bool isAdded = Operator::addParser<Factorial>();
}
