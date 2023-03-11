#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sin::call(const ArgumentsVector &argsVect) const {
  return sin(convert<Real>(argsVect.front())).toMinimalObject();
}

}
