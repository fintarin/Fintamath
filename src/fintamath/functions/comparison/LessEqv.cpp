#include "fintamath/functions/comparison/LessEqv.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  LessEqv::LessEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string LessEqv::toString() const {
    return "<=";
  }

  std::string LessEqv::getClassName() const {
    return "LessEqv";
  }

  Expression LessEqv::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return Boolean(argsVect.at(0).get().to<IComparable>() <= argsVect.at(1).get().to<IComparable>());
  }
}
