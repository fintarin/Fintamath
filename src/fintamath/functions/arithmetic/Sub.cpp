#include "fintamath/functions/arithmetic/Sub.hpp"

namespace fintamath {
  Expression Sub::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *(argsVect.at(0).get().to<IArithmetic>() - argsVect.at(1).get().to<IArithmetic>());
  }
}
