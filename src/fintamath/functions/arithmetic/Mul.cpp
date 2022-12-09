#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {
  Mul::Mul() : IOperatorCRTP(IOperator::Priority::Multiplication) {
  }

  std::string Mul::toString() const {
    return "*";
  }

  std::string Mul::getClassName() const {
    return "Mul";
  }

  Expression Mul::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return *(argsVect.at(0).get().to<IArithmetic>() * argsVect.at(1).get().to<IArithmetic>());
  }
}
