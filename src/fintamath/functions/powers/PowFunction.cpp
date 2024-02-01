#include "fintamath/functions/powers/PowFunction.hpp"

#include "fintamath/functions/powers/Pow.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> PowFunction::call(const ArgumentRefVector &argVect) const {
  return Pow{}(argVect);
}

}
