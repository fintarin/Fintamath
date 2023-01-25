#include "fintamath/functions/logic/And.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr And::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.front().get().to<Boolean>() && argsVect.back().get().to<Boolean>());
}

}
