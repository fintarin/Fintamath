#include "fintamath/functions/comparison/MoreEqv.hpp"

namespace fintamath {

MathObjectPtr MoreEqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) >=
                                   cast<IComparable>(argsVect.back().get()));
}

}
