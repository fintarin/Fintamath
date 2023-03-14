#include "fintamath/functions/logic/Nequiv.hpp"

namespace fintamath {

unique_ptr<IMathObject> Nequiv::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) != cast<Boolean>(argsVect.back().get()));
}

}
