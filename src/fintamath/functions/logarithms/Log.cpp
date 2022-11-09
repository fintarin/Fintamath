#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Log::toString() const {
    return "log";
  }

  std::string Log::getClassName() const {
    return "Log";
  }

  MathObjectPtr Log::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;

    return log(helpers::Converter::convert(argsVect.at(0), Rational())->to<Rational>(),
               helpers::Converter::convert(argsVect.at(1), Rational())->to<Rational>(), defaultPrecision)
        .simplify();
  }
}
