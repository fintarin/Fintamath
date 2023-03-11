#include "fintamath/functions/arithmetic/Sub.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sub::call(const ArgumentsVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) - cast<IArithmetic>(argsVect.back().get());
}

}
