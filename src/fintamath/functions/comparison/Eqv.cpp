#include "fintamath/functions/comparison/Eqv.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  Expression Eqv::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return {Boolean(argsVect.at(0).get() == argsVect.at(1).get())};
  }
}
