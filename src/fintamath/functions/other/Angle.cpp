#include "fintamath/functions/other/Angle.hpp"

#include "fintamath/functions/other/Rad.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Angle::call(const ArgumentsVector &argsVect) const {
  static const Rad RAD;
  return RAD(argsVect.front().get());
}

}
