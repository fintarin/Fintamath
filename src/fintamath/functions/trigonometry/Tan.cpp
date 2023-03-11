#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Tan::call(const ArgumentsVector &argsVect) const {
  return tan(convert<Real>(argsVect.front())).toMinimalObject();
}

}
