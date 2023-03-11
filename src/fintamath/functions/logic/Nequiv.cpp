#include "fintamath/functions/logic/Nequiv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Nequiv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) != cast<Boolean>(argsVect.back().get()));
}

}
