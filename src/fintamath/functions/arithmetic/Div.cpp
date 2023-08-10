#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Div::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<IArithmetic>(argsVect.front().get());
  const auto &rhs = cast<IArithmetic>(argsVect.back().get());

  if (lhs == Integer(0) && rhs == Integer(0)) {
    return Undefined().clone();
  }

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return multiDivSimplify(lhs, rhs);
}

std::unique_ptr<IMathObject> Div::multiDivSimplify(const IArithmetic &lhs, const IArithmetic &rhs) {
  static const auto multiDiv = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const IArithmetic &, const IArithmetic &)> outMultiPow;

    outMultiPow.add<Integer, Integer>([](const Integer &inLhs, const Integer &inRhs) {
      return divSimplify(inLhs, inRhs);
    });

    return outMultiPow;
  }();

  if (auto res = multiDiv(lhs, rhs)) {
    return res;
  }

  return lhs / rhs;
}

std::unique_ptr<IMathObject> Div::divSimplify(const Integer &lhs, const Integer &rhs) {
  if (lhs % rhs != 0) {
    return Rational(lhs, rhs).toMinimalObject();
  }

  return (lhs / rhs).toMinimalObject();
}

}
