#include "fintamath/functions/trigonometry/Asec.hpp"

#include <memory>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MultiMethod.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

using namespace detail;

std::unique_ptr<IMathObject> Asec::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<INumber>(argVect.front().get());

  if (rhs == Integer(-1)) {
    return Pi{}.toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return ComplexInf{}.clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiAsecSimplify(rhs);
}

std::unique_ptr<IMathObject> Asec::multiAsecSimplify(const INumber &rhs) {
  static const auto multiAsec = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsec;

    outMultiAsec.add<Integer>([](const Integer &inRhs) {
      return multiAsecSimplify(Real(inRhs));
    });

    outMultiAsec.add<Rational>([](const Rational &inRhs) {
      return multiAsecSimplify(Real(inRhs));
    });

    outMultiAsec.add<Real>([](const Real &inRhs) {
      return asec(inRhs).clone();
    });

    return outMultiAsec;
  }();

  return multiAsec(rhs);
}

}
