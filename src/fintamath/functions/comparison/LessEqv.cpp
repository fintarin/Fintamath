#include "fintamath/functions/comparison/LessEqv.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr LessEqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) <=
                                   cast<IComparable>(argsVect.back().get()));
}

}
