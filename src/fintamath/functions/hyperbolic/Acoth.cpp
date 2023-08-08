#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acoth::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return NegInf().clone();
  }

  // TODO! uncomment
  // if (rhs == Integer(0)) {
  //   return I Pi / 2;
  // }

  if (rhs == Integer(1)) {
    return Inf().clone();
  }

  return multiAcothSimpl(rhs);
}

std::unique_ptr<IMathObject> Acoth::multiAcothSimpl(const INumber &rhs) {
  static const auto multiAcoth = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAcoth;

    outMultiAcoth.add<Integer>([](const Integer &inRhs) {
      return multiAcothSimpl(Real(inRhs));
    });

    outMultiAcoth.add<Rational>([](const Rational &inRhs) {
      return multiAcothSimpl(Real(inRhs));
    });

    outMultiAcoth.add<Real>([](const Real &inRhs) {
      return acothSimpl(inRhs);
    });

    return outMultiAcoth;
  }();

  return multiAcoth(rhs);
}

std::unique_ptr<IMathObject> Acoth::acothSimpl(const Real &rhs) {
  try {
    return acoth(rhs).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
