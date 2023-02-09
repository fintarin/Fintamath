#include "fintamath/functions/comparison/Neqv.hpp"

namespace fintamath {

MathObjectPtr Neqv::call(const ArgumentsVector &argsVect) const {
  return std::make_unique<Boolean>(argsVect.front().get() != argsVect.back().get());
}

}
