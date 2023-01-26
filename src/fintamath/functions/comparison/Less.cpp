#include "fintamath/functions/comparison/Less.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Less::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<IComparable>(argsVect.front().get()) <
                                   cast<IComparable>(argsVect.back().get()));
}

}
