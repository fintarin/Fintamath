#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

MathObjectPtr Factorial::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = argsVect.at(0).get();

  if (!rhs.is<Integer>()) {
    throw UndefinedUnaryOpearatorException("!", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
  }

  return factorial(rhs.to<Integer>()).simplify();
}

}
