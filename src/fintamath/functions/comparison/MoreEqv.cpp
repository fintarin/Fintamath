#include "fintamath/functions/comparison/MoreEqv.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

MathObjectPtr MoreEqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.at(0).get().to<IComparable>() >= argsVect.at(1).get().to<IComparable>());
}

}
