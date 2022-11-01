#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {
  Neg::Neg() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string Neg::toString() const {
    return "-";
  }

  std::string Neg::getClassName() const {
    return "Neg";
  }

  MathObjectPtr Neg::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return -argsVect.at(0).get().to<IArithmetic>();
  }
}
