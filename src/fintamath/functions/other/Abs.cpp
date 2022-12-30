#include "fintamath/functions/other/Abs.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {
  Expression Abs::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    const auto &rhs = argsVect.at(0).get().to<INumber>();

    if (rhs < Integer(0)) {
      return *(-rhs);
    }

    return rhs;
  }
}
