#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/numbers/INumber.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/literals/constants/Indeterminate.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Div::call(const ArgumentsRefVector &argsVect) const {
  static const auto multiPow = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const IArithmetic &, const IArithmetic &)> outMultiPow;

    outMultiPow.add<Integer, Integer>([](const Integer &lhs, const Integer &rhs) {
      return divSimpl(lhs, rhs);
    });

    return outMultiPow;
  }();

  const auto &lhs = cast<IArithmetic>(argsVect.front().get());
  const auto &rhs = cast<IArithmetic>(argsVect.back().get());

  if (lhs == Integer(0) && rhs == Integer(0)) {
    return Indeterminate().clone();
  }

  if (rhs == Integer(0)) {
    return Inf().clone();
  }

  if (auto res = multiPow(lhs, rhs)) {
    return res;
  }

  return lhs / rhs;
}

std::unique_ptr<IMathObject> Div::divSimpl(const Integer &lhs, const Integer &rhs) {
  if (lhs % rhs != 0) {
    return Rational(lhs, rhs).toMinimalObject();
  }

  return (lhs / rhs).toMinimalObject();
}

}
