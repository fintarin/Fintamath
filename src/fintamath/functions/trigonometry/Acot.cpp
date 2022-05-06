#include "Acot.hpp"
#include "fintamath/functions/NamespaceFunctions.hpp"

namespace fintamath {
  std::string Acot::toString() const {
    return "acot";
  }

  MathObjectPtr Acot::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Number>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::acot(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Acot::equals(const Acot &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Acot::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Acot::operator()(argsVect.at(0).get());
  }
}