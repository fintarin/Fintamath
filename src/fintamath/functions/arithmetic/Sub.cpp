#include "fintamath/functions/arithmetic/Sub.hpp"

namespace fintamath {
  Sub::Sub() : OperatorCRTP(Operator::Priority::Addition) {
  }

  std::string Sub::toString() const {
    return "-";
  }

  MathObjectPtr Sub::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return argsVect.at(0).get().to<Arithmetic>() - argsVect.at(1).get().to<Arithmetic>();
  }

  static const bool isAdded = Operator::addParser<Sub>();
}
