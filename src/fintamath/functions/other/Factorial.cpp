#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/exceptions/UndefinedUnaryOperatorException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Factorial::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = argsVect.front().get();

  if (!is<Integer>(rhs)) {
    throw UndefinedUnaryOperatorException(toString(), rhs.toString(), UndefinedUnaryOperatorException::Type::Postfix);
  }

  return factorial(cast<Integer>(rhs), order).toMinimalObject();
}

}
