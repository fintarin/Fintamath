#include "fintamath/functions/comparison/More.hpp"

namespace fintamath {

MathObjectPtr More::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) >
                                   cast<IComparable>(argsVect.back().get()));
}

}
