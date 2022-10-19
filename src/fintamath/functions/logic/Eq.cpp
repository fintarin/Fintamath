#include "fintamath/functions/logic/Eq.hpp"

#include "fintamath/functions/Operator.hpp"
#include "fintamath/numbers/Number.hpp"

namespace fintamath {
  Eq::Eq() : OperatorCRTP(Operator::Priority::Comparison) {
  }

  std::string Eq::toString() const {
    return "=";
  }

  MathObjectPtr Eq::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    return Number::parse(int64_t(argsVect.at(0).get() == argsVect.at(1).get()));
  }

  static const bool isDefined = Operator::addParser<Eq>();
}
