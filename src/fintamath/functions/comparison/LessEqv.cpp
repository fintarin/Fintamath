#include "fintamath/functions/comparison/LessEqv.hpp"

namespace fintamath {

unique_ptr<IMathObject> LessEqv::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) <= cast<IComparable>(argsVect.back().get()));
}

}
