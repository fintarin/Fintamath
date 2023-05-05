#include "fintamath/core/IArithmetic.hpp"

#include "fintamath/meta/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> IArithmetic::multiAdd;
MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> IArithmetic::multiSub;
MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> IArithmetic::multiMul;
MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> IArithmetic::multiDiv;

}

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
