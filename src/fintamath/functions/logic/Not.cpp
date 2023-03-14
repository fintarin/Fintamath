#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

unique_ptr<IMathObject> Not::call(const ArgumentsRefVector &argsVect) const {
  return make_unique<Boolean>(!cast<Boolean>(argsVect.front().get()));
}

}
