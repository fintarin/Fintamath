#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

const Integer PERCENT_VALUE = 100;

unique_ptr<IMathObject> Percent::call(const ArgumentsRefVector &argsVect) const {
  return (cast<INumber>(argsVect.front().get()) / PERCENT_VALUE)->toMinimalObject();
}

}
