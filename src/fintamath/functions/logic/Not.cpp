#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Not::call(const ArgumentsRefVector &argsVect) const {
  return std::make_unique<Boolean>(!cast<Boolean>(argsVect.front().get()));
}

}
