#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cos::call(const ArgumentsRefVector &argsVect) const {
  return cos(convert<Real>(argsVect.front())).toMinimalObject();
}

}
