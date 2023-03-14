#include "fintamath/functions/arithmetic/Sign.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

unique_ptr<IMathObject> Sign::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Integer>(convert<Real>(argsVect.front().get()).sign());
}

}
