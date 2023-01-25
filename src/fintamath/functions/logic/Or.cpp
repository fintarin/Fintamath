#include "fintamath/functions/logic/Or.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Or::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.front().get().to<Boolean>() || argsVect.back().get().to<Boolean>());
}

}
