#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

MathObjectPtr Factorial::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = argsVect.at(0).get();

  if (!rhs.instanceof <Integer>()) {
    throw UndefinedUnaryOpearatorException(toString(), rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
  }

  return factorial(rhs.to<Integer>(), order).simplify();
}

}
