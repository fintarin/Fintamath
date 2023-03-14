#include "fintamath/functions/logic/And.hpp"

namespace fintamath {

unique_ptr<IMathObject> And::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) && cast<Boolean>(argsVect.back().get()));
}

}
