#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/exceptions/UndefinedUnaryOperatorException.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Percent::call(const ArgumentsRefVector &argsVect) const {
  static const Integer PERCENT_VALUE = 100;
  return (cast<INumber>(argsVect.front().get()) / PERCENT_VALUE)->toMinimalObject();
}

}
