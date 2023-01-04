#include "fintamath/functions/comparison/Neqv.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

MathObjectPtr Neqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.at(0).get() != argsVect.at(1).get());
}

}
