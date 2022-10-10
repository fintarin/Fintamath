#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Lb::toString() const {
    return "lb";
  }

  MathObjectPtr Lb::operator()(const MathObject &rhs) const {
    constexpr int64_t defaultPrecision = 45;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Rhs must be Arithmetic");
    }
    auto newRhs = meta::convertMathObject(rhs, Rational());
    return lb(newRhs->to<Rational>(), defaultPrecision).simplify();
  }

  MathObjectPtr Lb::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Lb::operator()(argsVect.at(0).get());
  }
}