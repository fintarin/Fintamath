#include "fintamath/functions/ntheory/Floor.hpp"

#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RationalFunctions.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Floor::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  return multiFloorSimplify(rhs);
}

std::unique_ptr<IMathObject> Floor::multiFloorSimplify(const INumber &rhs) {
  static const auto multiFloor = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiFloor;

    outMultiFloor.add<Integer>([](const Integer &inRhs) {
      return inRhs.clone();
    });

    outMultiFloor.add<Rational>([](const Rational &inRhs) {
      return floor(inRhs).clone();
    });

    outMultiFloor.add<Real>([](const Real &inRhs) {
      Integer res = floor(inRhs);

      if (abs(inRhs) == Real(abs(res))) {
        return std::unique_ptr<IMathObject>{};
      }

      return std::move(res).clone();
    });

    outMultiFloor.add<Complex>([](const Complex &inRhs) {
      const auto re = cast<INumber>(multiFloorSimplify(inRhs.real()));
      const auto im = cast<INumber>(multiFloorSimplify(inRhs.imag()));

      if (!re || !im) {
        return std::unique_ptr<IMathObject>{};
      }

      return Complex(*re, *im).toMinimalObject();
    });

    return outMultiFloor;
  }();

  return multiFloor(rhs);
}

}
