#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cot::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return multiCotSimplify(rhs);
}

std::unique_ptr<IMathObject> Cot::multiCotSimplify(const INumber &rhs) {
  static const auto multiCot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiCot;

    outMultiCot.add<Integer>([](const Integer &inRhs) {
      return multiCotSimplify(Real(inRhs));
    });

    outMultiCot.add<Rational>([](const Rational &inRhs) {
      return multiCotSimplify(Real(inRhs));
    });

    outMultiCot.add<Real>([](const Real &inRhs) {
      return cotSimplify(inRhs);
    });

    return outMultiCot;
  }();

  return multiCot(rhs);
}

std::unique_ptr<IMathObject> Cot::cotSimplify(const Real &rhs) {
  try {
    return cot(rhs).clone();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
