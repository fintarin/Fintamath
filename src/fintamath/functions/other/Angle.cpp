#include "fintamath/functions/other/Angle.hpp"

#include "fintamath/functions/other/Rad.hpp"

namespace fintamath {

const Rad RAD;

std::unique_ptr<IMathObject> Angle::call(const ArgumentsRefVector &argsVect) const {
  return RAD(argsVect.front().get());
}

}
