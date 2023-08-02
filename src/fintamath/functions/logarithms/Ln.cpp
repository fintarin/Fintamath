#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Ln::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return NegInf().clone();
  }

  return ln(convert<Real>(rhs)).toMinimalObject();
}

}
