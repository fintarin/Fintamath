#include "fintamath/functions/comparison/MoreEqv.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {
  MoreEqv::MoreEqv() : IOperatorCRTP(IOperator::Priority::Comparison) {
  }

  std::string MoreEqv::toString() const {
    return "=";
  }

  std::string MoreEqv::getClassName() const {
    return "MoreEqv";
  }

  MathObjectPtr MoreEqv::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return std::make_unique<Boolean>(argsVect.at(0).get().to<IComparable>() >= argsVect.at(1).get().to<IComparable>());
  }
}
