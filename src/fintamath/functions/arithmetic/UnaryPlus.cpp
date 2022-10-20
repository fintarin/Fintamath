#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {
  UnaryPlus::UnaryPlus() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string UnaryPlus::toString() const {
    return "+";
  }

  MathObjectPtr UnaryPlus::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return +argsVect.at(0).get().to<IArithmetic>();
  }

  static const bool isAdded = IOperator::addParser<UnaryPlus>();
}
