#include "fintamath/functions/comparison/Less.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  Less::Less() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string Less::toString() const {
    return "<";
  }

  std::string Less::getClassName() const {
    return "Less";
  }

  Expression Less::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return Boolean(argsVect.at(0).get().to<IComparable>() < argsVect.at(1).get().to<IComparable>());
  }
}
