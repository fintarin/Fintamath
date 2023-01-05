#include "fintamath/functions/comparison/Less.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Less::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.at(0).get().to<IComparable>() < argsVect.at(1).get().to<IComparable>());
}

}
