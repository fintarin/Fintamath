#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Percent::call(const ArgumentRefVector &argVect) const {
  static const Rational percentVal = 100;
  const auto &rhs = cast<INumber>(argVect.front().get());

  return (rhs / percentVal)->toMinimalObject();
}

}
