#include "fintamath/functions/logic/Impl.hpp"

#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

MathObjectPtr Impl::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(!argsVect.front().get().to<Boolean>() || argsVect.back().get().to<Boolean>());
}

}
