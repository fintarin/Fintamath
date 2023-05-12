#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sqrt::call(const ArgumentsRefVector &argsVect) const {
  static const auto multiSqrt = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiSqrt;

    outMultiSqrt.add<Integer>([](const Integer &rhs) {
      Integer remainder;

      auto res = std::make_unique<Integer>(sqrt(rhs, remainder));
      if (remainder == 0) {
        return res->toMinimalObject();
      }

      return sqrt(convert<Real>(rhs)).toMinimalObject();
    });

    outMultiSqrt.add<Rational>([](const Rational &rhs) {
      Integer remainder;

      Integer numerator = sqrt(rhs.numerator(), remainder);
      if (remainder != 0) {
        return sqrt(convert<Real>(rhs)).toMinimalObject();
      }

      Integer denominator = sqrt(rhs.denominator(), remainder);
      if (remainder != 0) {
        return sqrt(convert<Real>(rhs)).toMinimalObject();
      }

      return Rational(numerator, denominator).toMinimalObject();
    });

    outMultiSqrt.add<Real>([](const Real &rhs) {
      return std::make_unique<Real>(sqrt(rhs));
    });

    return outMultiSqrt;
  }();

  const auto &rhs = cast<INumber>(argsVect.front().get());

  return multiSqrt(rhs);
}

}
