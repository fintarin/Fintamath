#include "fintamath/functions/powers/PowFunction.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/powers/Pow.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> PowFunction::call(const ArgumentRefVector &argVect) const {
  return Pow{}(argVect);
}

}
