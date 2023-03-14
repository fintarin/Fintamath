#include "fintamath/functions/comparison/Eqv.hpp"

namespace fintamath {

unique_ptr<IMathObject> Eqv::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(argsVect.front().get() == argsVect.back().get());
}

}
