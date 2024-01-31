#include "fintamath/functions/trigonometry/Csc.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Csc::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return multiCscSimplify(rhs);
}

std::unique_ptr<IMathObject> Csc::multiCscSimplify(const INumber &rhs) {
  static const auto multiCsc = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCsc;

    outMultiCsc.add<Integer>([](const Integer &inRhs) {
      return multiCscSimplify(Real(inRhs));
    });

    outMultiCsc.add<Rational>([](const Rational &inRhs) {
      return multiCscSimplify(Real(inRhs));
    });

    outMultiCsc.add<Real>([](const Real &inRhs) {
      return csc(inRhs).clone();
    });

    return outMultiCsc;
  }();

  return multiCsc(rhs);
}

}
