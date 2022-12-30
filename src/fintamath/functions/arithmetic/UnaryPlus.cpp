#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {
  Expression UnaryPlus::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *(+argsVect.at(0).get().to<IArithmetic>());
  }
}
