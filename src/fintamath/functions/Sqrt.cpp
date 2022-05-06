#include "Sqrt.hpp"
#include "NamespaceFunctions.hpp"

namespace fintamath {

  std::string Sqrt::toString() const {
    return "sqrt";
  }

  MathObjectPtr Sqrt::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::sqrt(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Sqrt::equals(const Sqrt &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Sqrt::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Sqrt::operator()(argsVect.at(0).get());
  }

}