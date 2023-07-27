#include "fintamath/numbers/INumber.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
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
