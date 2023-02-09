#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

MathObjectPtr Or::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(cast<Boolean>(argsVect.front().get()) || cast<Boolean>(argsVect.back().get()));
}

}
