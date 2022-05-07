#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Acos::toString() const {
    return "acos";
  }

  MathObjectPtr Acos::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::acos(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Acos::equals(const Acos & /*rhs*/) const {
    return true;
  }

  MathObjectPtr Acos::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Acos::operator()(argsVect.at(0).get());
  }
}