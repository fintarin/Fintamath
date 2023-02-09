#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

MathObjectPtr Not::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(!cast<Boolean>(argsVect.front().get()));
}

}
