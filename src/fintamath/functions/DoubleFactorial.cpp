#include "DoubleFactorial.hpp"
#include "NamespaceFunctions.hpp"

namespace fintamath {
  std::string DoubleFactorial::toString() const {
    return "!!";
  }

  MathObjectPtr DoubleFactorial::operator()(const MathObject &rhs) const {
    if (!rhs.is<Integer>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::doubleFactorial(newRhs->to<Rational>()));
  }

  bool DoubleFactorial::equals(const DoubleFactorial &/*rhs*/) const {
    return true;
  }

  MathObjectPtr DoubleFactorial::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 1) {
      throw std::invalid_argument("The number of arguments must be 1");
    }
    return DoubleFactorial::operator()(argsVect.at(0).get());
  }
}
