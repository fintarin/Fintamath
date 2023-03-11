#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Atan::call(const ArgumentsVector &argsVect) const {
  return atan(convert<Real>(argsVect.front())).toMinimalObject();
}

}
