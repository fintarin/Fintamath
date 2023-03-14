#include "fintamath/functions/comparison/More.hpp"

namespace fintamath {

unique_ptr<IMathObject> More::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) > cast<IComparable>(argsVect.back().get()));
}

}
