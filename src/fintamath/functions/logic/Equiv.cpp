#include "fintamath/functions/logic/Equiv.hpp"

namespace fintamath {

unique_ptr<IMathObject> Equiv::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) == cast<Boolean>(argsVect.back().get()));
}

}
