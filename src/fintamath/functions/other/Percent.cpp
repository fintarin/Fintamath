#include "Percent.hpp"
#include "fintamath/functions/NamespaceFunctions.hpp"

namespace fintamath {
  std::string Percent::toString() const {
    return "%";
  }

  MathObjectPtr Percent::operator()(const MathObject &rhs) const {
    const int64_t percentValue = 100;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(newRhs->to<Rational>() / percentValue);
  }

  bool Percent::equals(const Percent &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Percent::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Percent::operator()(argsVect.at(0).get());
  }
}
