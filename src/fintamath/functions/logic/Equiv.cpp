#include "fintamath/functions/logic/Equiv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Equiv::call(const ArgumentsRefVector &argsVect) const {
  return std::make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) == cast<Boolean>(argsVect.back().get()));
}

}
