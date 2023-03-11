#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Mul::call(const ArgumentsVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) * cast<IArithmetic>(argsVect.back().get());
}

}
