#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Exp::toString() const {
    return "exp";
  }

  MathObjectPtr Exp::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::exp(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Exp::equals(const Exp & /*rhs*/) const {
    return true;
  }

  MathObjectPtr Exp::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Exp::operator()(argsVect.at(0).get());
  }
}