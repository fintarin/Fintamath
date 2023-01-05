#include "fintamath/functions/logic/Not.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Not::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(!argsVect.at(0).get().to<Boolean>());
}

}
