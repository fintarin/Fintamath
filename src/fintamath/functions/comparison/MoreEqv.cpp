#include "fintamath/functions/comparison/MoreEqv.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr MoreEqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.front().get().to<IComparable>() >= argsVect.back().get().to<IComparable>());
}

}
