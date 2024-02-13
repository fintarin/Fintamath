#include "fintamath/functions/hyperbolic/Atanh.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Atanh::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    return NegInf{}.clone();
  }

  if (rhs == Integer(0)) {
    return rhs.clone();
  }

  if (rhs == Integer(1)) {
    return Inf{}.clone();
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
      return atanh(inRhs).clone();
    });

    return outMultiAtanh;
  }();

  return multiAtanh(rhs);
}

}
