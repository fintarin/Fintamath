#include "fintamath/functions/comparison/Less.hpp"

namespace fintamath {

unique_ptr<IMathObject> Less::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) < cast<IComparable>(argsVect.back().get()));
}

}
