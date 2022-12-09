#include "fintamath/functions/factorials/DoubleFactorial.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {
  DoubleFactorial::DoubleFactorial() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string DoubleFactorial::toString() const {
    return "!!";
  }

  std::string DoubleFactorial::getClassName() const {
    return "DoubleFactorial";
  }

  Expression DoubleFactorial::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    const auto &rhs = argsVect.at(0).get();

    if (!rhs.is<Integer>()) {
      throw UndefinedUnaryOpearatorException("!!", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
    }

    return doubleFactorial(rhs.to<Integer>());
  }
}
