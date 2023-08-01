#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

const Rational PERCENT_VALUE = 100;

std::unique_ptr<IMathObject> Percent::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());
  return (rhs / PERCENT_VALUE)->toMinimalObject();
}

}
