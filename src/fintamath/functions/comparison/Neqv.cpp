#include "fintamath/functions/comparison/Neqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Neqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.front().get() != argsVect.back().get());
}

}
