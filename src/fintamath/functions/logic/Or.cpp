#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

unique_ptr<IMathObject> Or::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) || cast<Boolean>(argsVect.back().get()));
}

}
