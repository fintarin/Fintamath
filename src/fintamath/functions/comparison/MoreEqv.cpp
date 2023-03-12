#include "fintamath/functions/comparison/MoreEqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> MoreEqv::call(const ArgumentsRefVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) >=
                                   cast<IComparable>(argsVect.back().get()));
}

}
