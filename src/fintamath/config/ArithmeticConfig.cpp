#include "fintamath/core/IArithmetic.hpp"

#include "fintamath/meta/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &IArithmetic::getMultiAdd() {
  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> multiAdd;
  return multiAdd;
}

MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &IArithmetic::getMultiSub() {
  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> multiSub;
  return multiSub;
}

MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &IArithmetic::getMultiMul() {
  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> multiMul;
  return multiMul;
}

MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> &IArithmetic::getMultiDiv() {
  static MultiMethod<std::unique_ptr<IArithmetic>(const IArithmetic &, const IArithmetic &)> multiDiv;
  return multiDiv;
}

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
