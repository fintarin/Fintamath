#include "fintamath/functions/logic/And.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr And::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.at(0).get().to<Boolean>() && argsVect.at(1).get().to<Boolean>());
}

}
