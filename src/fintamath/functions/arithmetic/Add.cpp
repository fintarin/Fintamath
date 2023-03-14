#include "fintamath/functions/arithmetic/Add.hpp"

namespace fintamath {

unique_ptr<IMathObject> Add::call(const ArgumentsRefVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) + cast<IArithmetic>(argsVect.back().get());
}

}
