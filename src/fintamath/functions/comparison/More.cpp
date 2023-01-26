#include "fintamath/functions/comparison/More.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr More::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) >
                                   cast<IComparable>(argsVect.back().get()));
}

}
