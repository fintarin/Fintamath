#include "Cot.hpp"

#include "fintamath/functions/Function.hpp"
#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Cot::toString() const {
    return "cot";
  }

  MathObjectPtr Cot::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::cot(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Cot::equals(const Cot &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Cot::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Cot::operator()(argsVect.at(0).get());
  }
}
