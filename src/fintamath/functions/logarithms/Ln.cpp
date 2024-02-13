#include "fintamath/functions/logarithms/Ln.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Ln::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(0)) {
    return NegInf{}.clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiLnSimplify(rhs);
}

std::unique_ptr<IMathObject> Ln::multiLnSimplify(const INumber &rhs) {
  static const auto multiLn = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiLn;

    outMultiLn.add<Integer>([](const Integer &inRhs) {
      return multiLnSimplify(Real(inRhs));
    });

    outMultiLn.add<Rational>([](const Rational &inRhs) {
      return multiLnSimplify(Real(inRhs));
    });

    outMultiLn.add<Real>([](const Real &inRhs) {
      return ln(inRhs).clone();
    });

    return outMultiLn;
  }();

  return multiLn(rhs);
}

}
