#include "Ln.hpp"
#include "fintamath/functions/NamespaceFunctions.hpp"

namespace fintamath {
  std::string Ln::toString() const {
    return "ln";
  }

  MathObjectPtr Ln::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::ln(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Ln::equals(const Ln &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Ln::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Ln::operator()(argsVect.at(0).get());
  }
}

