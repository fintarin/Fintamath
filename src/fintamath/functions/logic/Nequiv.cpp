#include "fintamath/functions/logic/Nequiv.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Nequiv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.at(0).get().to<Boolean>() != argsVect.at(1).get().to<Boolean>());
}

}
