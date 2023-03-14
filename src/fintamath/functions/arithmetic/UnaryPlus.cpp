#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {

unique_ptr<IMathObject> UnaryPlus::call(const ArgumentsRefVector &argsVect) const {
  return +cast<IArithmetic>(argsVect.front().get());
}

}
