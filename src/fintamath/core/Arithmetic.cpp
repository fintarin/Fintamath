#include "fintamath/core/Arithmetic.hpp"

#include "fintamath/meta/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {
  auto initMultiDiv() {
    meta::MultiMethod<ArithmeticPtr(const Arithmetic &, const Arithmetic &)> multiDiv;
    multiDiv.add<Integer, Integer>([](const Integer &lhs, const Integer &rhs) {
      auto res = (Rational(lhs) / Rational(rhs)).simplify();
      return meta::castPtr<Arithmetic>(res);
    });
    return multiDiv;
  }

  const auto mDiv = initMultiDiv();

  ArithmeticPtr multiDiv(const Arithmetic &lhs, const Arithmetic &rhs) {
    return mDiv(lhs, rhs);
  }
}
