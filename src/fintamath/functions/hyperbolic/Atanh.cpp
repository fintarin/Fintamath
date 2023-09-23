#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Atanh::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return NegInf().clone();
  }

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  if (rhs == Integer(1)) {
    return Inf().clone();
  }

  return multiAtanhSimplify(rhs);
}

std::unique_ptr<IMathObject> Atanh::multiAtanhSimplify(const INumber &rhs) {
  static const auto multiAtanh = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAtanh;

    outMultiAtanh.add<Integer>([](const Integer &inRhs) {
      return multiAtanhSimplify(Real(inRhs));
    });

    outMultiAtanh.add<Rational>([](const Rational &inRhs) {
      return multiAtanhSimplify(Real(inRhs));
    });

    outMultiAtanh.add<Real>([](const Real &inRhs) {
      return atanhSimplify(inRhs);
    });

    return outMultiAtanh;
  }();

  return multiAtanh(rhs);
}

std::unique_ptr<IMathObject> Atanh::atanhSimplify(const Real &rhs) {
  try {
    return atanh(rhs).toMinimalObject();
  }
  catch (const UndefinedException &) {
    return {};
  }
}

}
