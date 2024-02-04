#include "fintamath/functions/arithmetic/Abs.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RationalFunctions.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Abs::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  return multiAbsSimplify(rhs);
}

std::unique_ptr<IMathObject> Abs::multiAbsSimplify(const INumber &rhs) {
  static const auto multiAbs = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAbs;

    outMultiAbs.add<Integer>([](const Integer &inRhs) {
      return abs(inRhs).clone();
    });

    outMultiAbs.add<Rational>([](const Rational &inRhs) {
      return abs(inRhs).clone();
    });

    outMultiAbs.add<Real>([](const Real &inRhs) {
      return abs(inRhs).clone();
    });

    outMultiAbs.add<Complex>([](const Complex &inRhs) {
      // https://en.wikipedia.org/wiki/Absolute_value#Complex_numbers
      const auto sumOfSquares = *(inRhs.real() * inRhs.real()) + *(inRhs.imag() * inRhs.imag());
      return Sqrt{}(*sumOfSquares);
    });

    return outMultiAbs;
  }();

  return multiAbs(rhs);
}

}
