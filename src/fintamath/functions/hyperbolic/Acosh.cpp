#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acosh::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  // TODO! uncomment
  // if (rhs == Integer(-1)) {
  //   return I Pi;
  // }

  // TODO! uncomment
  // if (rhs == Integer(0)) {
  //   return I Pi / 2;
  // }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiAcoshSimpl(rhs);
}

std::unique_ptr<IMathObject> Acosh::multiAcoshSimpl(const INumber &rhs) {
  static const auto multiAcosh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcosh;

    outMultiAcosh.add<Integer>([](const Integer &inRhs) {
      return multiAcoshSimpl(Real(inRhs));
    });

    outMultiAcosh.add<Rational>([](const Rational &inRhs) {
      return multiAcoshSimpl(Real(inRhs));
    });

    outMultiAcosh.add<Real>([](const Real &inRhs) {
      return acoshSimpl(inRhs);
    });

    return outMultiAcosh;
  }();

  return multiAcosh(rhs);
}

std::unique_ptr<IMathObject> Acosh::acoshSimpl(const Real &rhs) {
  try {
    return acosh(rhs).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
