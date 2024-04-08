#include "fintamath/functions/ntheory/Ceil.hpp"

#include <memory>
#include <utility>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RationalFunctions.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Ceil)

using namespace detail;

std::unique_ptr<IMathObject> Ceil::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  return multiCeilSimplify(rhs);
}

std::unique_ptr<IMathObject> Ceil::multiCeilSimplify(const INumber &rhs) {
  static const auto multiCeil = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCeil;

    outMultiCeil.add<Integer>([](const Integer &inRhs) {
      return inRhs.clone();
    });

    outMultiCeil.add<Rational>([](const Rational &inRhs) {
      return ceil(inRhs).clone();
    });

    outMultiCeil.add<Real>([](const Real &inRhs) {
      Integer res = ceil(inRhs);

      if (abs(inRhs) == Real(abs(res))) {
        return std::unique_ptr<IMathObject>{};
      }

      return std::move(res).clone();
    });

    outMultiCeil.add<Complex>([](const Complex &inRhs) {
      const auto re = cast<INumber>(multiCeilSimplify(inRhs.real()));
      const auto im = cast<INumber>(multiCeilSimplify(inRhs.imag()));

      if (!re || !im) {
        return std::unique_ptr<IMathObject>{};
      }

      return Complex(*re, *im).toMinimalObject();
    });

    return outMultiCeil;
  }();

  return multiCeil(rhs);
}

}
