#include "fintamath/functions/comparison/Neqv.hpp"

namespace fintamath {

unique_ptr<IMathObject> Neqv::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(argsVect.front().get() != argsVect.back().get());
}

}
