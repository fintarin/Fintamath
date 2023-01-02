#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

constexpr int64_t PERCENT_VALUE = 100;

MathObjectPtr Percent::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = argsVect.at(0).get();

  if (!rhs.is<Integer>()) {
    throw UndefinedUnaryOpearatorException("%", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
  }

  return (Rational(rhs.to<Integer>()) / PERCENT_VALUE).simplify();
}

}
