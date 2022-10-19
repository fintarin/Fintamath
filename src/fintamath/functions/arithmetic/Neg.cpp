#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {
  Neg::Neg() : OperatorCRTP(Operator::Priority::PrefixUnary) {
  }

  std::string Neg::toString() const {
    return "-";
  }

  MathObjectPtr Neg::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return -argsVect.at(0).get().to<Arithmetic>();
  }

  static const bool isAdded = Operator::addParser<Neg>();
}
