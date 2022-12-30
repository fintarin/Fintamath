#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

Expression Neg::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
  return *(-argsVect.at(0).get().to<IArithmetic>());
}

}
