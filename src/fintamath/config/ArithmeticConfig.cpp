#include "fintamath/config/ArithmeticConfig.hpp"

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/multimethod/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> IArithmetic::multiAdd;
MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> IArithmetic::multiSub;
MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> IArithmetic::multiMul;
MultiMethod<ArithmeticPtr(const IArithmetic &, const IArithmetic &)> IArithmetic::multiDiv;

static const ArithmeticConfig config;

ArithmeticConfig::ArithmeticConfig() {
  IArithmetic::addMultiDivFunction<Integer, Integer>([](const Integer &lhs, const Integer &rhs) {
    return castPtr<IArithmetic>((Rational(lhs) / Rational(rhs)).simplify());
  });
}

}
