#include "fintamath/functions/arithmetic/Add.hpp"

namespace fintamath {
  Add::Add() : OperatorCRTP(Operator::Priority::Addition) {
  }

  std::string Add::toString() const {
    return "+";
  }

  MathObjectPtr Add::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return argsVect.at(0).get().to<Arithmetic>() + argsVect.at(1).get().to<Arithmetic>();
  }

  static const bool isDefined = Operator::addParser<Add>();
}
