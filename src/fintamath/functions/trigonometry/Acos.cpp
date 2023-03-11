#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acos::call(const ArgumentsVector &argsVect) const {
  return acos(convert<Real>(argsVect.front())).toMinimalObject();
}

}
