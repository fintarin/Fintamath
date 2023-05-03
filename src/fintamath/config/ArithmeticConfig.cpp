#include "fintamath/core/IArithmetic.hpp"

#include "fintamath/meta/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

struct ArithmeticConfig {
  ArithmeticConfig() {
    IArithmetic::addMultiDivFunction<Integer, Integer>([](const Integer &lhs, const Integer &rhs) {
      return cast<IArithmetic>((Rational(lhs) / Rational(rhs)).toMinimalObject());
    });
  }
};

const ArithmeticConfig config;
}
