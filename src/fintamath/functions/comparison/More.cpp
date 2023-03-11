#include "fintamath/functions/comparison/More.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> More::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) >
                                   cast<IComparable>(argsVect.back().get()));
}

}
