#include "fintamath/functions/logic/Impl.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Impl::call(const ArgumentsRefVector &argsVect) const {
  return std::make_unique<Boolean>(!cast<Boolean>(argsVect.front().get()) || cast<Boolean>(argsVect.back().get()));
}

}
