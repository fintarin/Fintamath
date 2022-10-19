#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {
  Div::Div() : OperatorCRTP(Operator::Priority::Multiplication) {
  }

  std::string Div::toString() const {
    return "/";
  }

  MathObjectPtr Div::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return argsVect.at(0).get().to<Arithmetic>() / argsVect.at(1).get().to<Arithmetic>();
  }

  static const bool isDefined = Operator::addParser<Div>();
}
