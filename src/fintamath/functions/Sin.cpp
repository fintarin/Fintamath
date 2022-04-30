#include "Sin.hpp"
#include "NamespaceFunctions.hpp"

namespace fintamath {
  std::string Sin::toString() const {
    return "sin";
  }

  MathObjectPtr Sin::operator()(const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::sin(newRhs->to<Rational>(), defaultPrecision));
  }

  bool Sin::equals(const Sin &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Sin::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return Sin::operator()(argsVect.at(0).get());
  }
}