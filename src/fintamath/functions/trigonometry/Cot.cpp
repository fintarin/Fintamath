#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cot::call(const ArgumentsRefVector &argsVect) const {
  return cot(convert<Real>(argsVect.front().get())).toMinimalObject();
}

}
