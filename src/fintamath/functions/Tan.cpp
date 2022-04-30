#include "Tan.hpp"
#include "NamespaceFunctions.hpp"

namespace fintamath {
  std::string Tan::toString() const {
    return "tan";
  }

  MathObjectPtr Tan::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::tan(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Tan::equals(const Tan &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Tan::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Tan::operator()(argsVect.at(0).get());
  }
}
