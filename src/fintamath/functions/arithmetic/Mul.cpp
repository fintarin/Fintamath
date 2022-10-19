#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {
  Mul::Mul() : OperatorCRTP(Operator::Priority::Multiplication) {
  }

  std::string Mul::toString() const {
    return "*";
  }

  MathObjectPtr Mul::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return argsVect.at(0).get().to<Arithmetic>() * argsVect.at(1).get().to<Arithmetic>();
  }

  static const bool isAdded = Operator::addParser<Mul>();
}
