#include "fintamath/functions/comparison/LessEqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> LessEqv::call(const ArgumentsRefVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) <=
                                   cast<IComparable>(argsVect.back().get()));
}

}
