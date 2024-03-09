#include "fintamath/functions/arithmetic/AddOper.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> AddOper::call(const ArgumentRefVector &argVect) const {
  return Add{}(argVect);
}

}
