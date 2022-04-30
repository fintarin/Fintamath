#include "Atan.hpp"
#include "NamespaceFunctions.hpp"

namespace fintamath {
  std::string Atan::toString() const {
    return "atan";
  }

  MathObjectPtr Atan::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::atan(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Atan::equals(const Atan &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Atan::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Atan::operator()(argsVect.at(0).get());
  }
}