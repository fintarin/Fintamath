#include "Log.hpp"
#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {

  std::string Log::toString() const {
    return "log";
  }

  MathObjectPtr Log::operator()(const MathObject &lhs, const MathObject &rhs) const {
    const int64_t defaultPrecision = 36;
    if (!rhs.instanceOf<Arithmetic>()) {
      throw std::invalid_argument("Types must be Arithmetic");
    }

    auto newLhs = meta::convertRhsToLhsType(Rational(), lhs);
    auto newRhs = meta::convertRhsToLhsType(Rational(), rhs);
    return std::make_unique<Rational>(functions::log(newLhs->to<Rational>(), newRhs->to<Rational>(), defaultPrecision));
  }

  bool Log::equals(const Log &/*rhs*/) const {
    return true;
  }

  MathObjectPtr Log::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    if (argsVect.size() != 2) {
      throw std::invalid_argument("The number of arguments must be 2");
    }
    return Log::operator()(argsVect.at(0).get(), argsVect.at(1).get());
  }

}