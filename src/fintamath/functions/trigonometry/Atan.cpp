#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

unique_ptr<IMathObject> Atan::call(const ArgumentsRefVector &argsVect) const {
  return atan(convert<Real>(argsVect.front())).toMinimalObject();
}

}
