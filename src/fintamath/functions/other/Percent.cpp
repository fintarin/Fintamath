#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Percent::call(const ArgumentRefVector &argsVect) const {
  static const Rational percentVal = 100;
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return (rhs / percentVal)->toMinimalObject();
}

}
