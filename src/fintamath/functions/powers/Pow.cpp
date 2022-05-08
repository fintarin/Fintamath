#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Pow::toString() const {
    return "^";
  }

  int Pow::getPriority() const {
    return priority;
  }

  MathObjectPtr Pow::operator()(const MathObject &lhs, const MathObject &rhs) const {
    const int64_t defaultPrecision = 45;
    if (!lhs.instanceOf<Arithmetic>() || !rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Lhs and Rhs must be Arithmetic");
    }
    auto newLhs = meta::convertRhsToLhsType(Rational(), lhs);
    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return pow(newLhs->to<Rational>(), newRhs->to<Rational>(), defaultPrecision).simplify();
  }

  MathObjectPtr Pow::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 2) {
      throw std::invalid_argument("The number of arguments must be 2");
    }
    return Pow::operator()(argsVect.at(0).get(), argsVect.at(1).get());
  }
}
