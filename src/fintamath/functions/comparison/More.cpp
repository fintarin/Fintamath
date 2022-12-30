#include "fintamath/functions/comparison/More.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  More::More() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string More::toString() const {
    return ">";
  }

  Expression More::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return Boolean(argsVect.at(0).get().to<IComparable>() > argsVect.at(1).get().to<IComparable>());
  }
}
