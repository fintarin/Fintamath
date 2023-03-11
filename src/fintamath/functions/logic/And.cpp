#include "fintamath/functions/logic/And.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> And::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) && cast<Boolean>(argsVect.back().get()));
}

}
