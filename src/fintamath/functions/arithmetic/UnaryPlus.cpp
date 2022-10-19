#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {
  UnaryPlus::UnaryPlus() : OperatorCRTP(Operator::Priority::PrefixUnary) {
  }

  std::string UnaryPlus::toString() const {
    return "+";
  }

  MathObjectPtr UnaryPlus::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return +argsVect.at(0).get().to<Arithmetic>();
  }

  static const bool isDefined = Operator::addParser<UnaryPlus>();
}
