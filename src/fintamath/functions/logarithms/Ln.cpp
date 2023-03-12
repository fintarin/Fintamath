#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Ln::call(const ArgumentsRefVector &argsVect) const {
  return ln(convert<Real>(argsVect.front())).toMinimalObject();
}

}
