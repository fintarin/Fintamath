#include "fintamath/functions/logic/Impl.hpp"

namespace fintamath {

unique_ptr<IMathObject> Impl::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(!cast<Boolean>(argsVect.front().get()) || cast<Boolean>(argsVect.back().get()));
}

}
