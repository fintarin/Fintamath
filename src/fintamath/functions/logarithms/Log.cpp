#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Log::toString() const {
    return "log";
  }

  MathObjectPtr Log::call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;

    return log(meta::convertMathObject(argsVect.at(0), Rational())->to<Rational>(),
               meta::convertMathObject(argsVect.at(1), Rational())->to<Rational>(), defaultPrecision)
        .simplify();
  }

  static const bool isAdded = Function::addParser<Log>();
}
