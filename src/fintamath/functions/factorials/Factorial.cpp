#include "fintamath/functions/factorials/Factorial.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
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
    const auto &rhs = argsVect.at(0).get();

    if (!rhs.is<Integer>()) {
      throw UndefinedUnaryOpearatorException("!", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
    }

    return std::make_unique<Integer>(factorial(rhs.to<Integer>()));
  }
}
