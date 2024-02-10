#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Tanh.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Tanh;
const F f;

TEST(TanhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "tanh");
}

TEST(TanhTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(TanhTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(TanhTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(TanhTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(TanhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(5))->toString(), "0.99990920426259513121");
  EXPECT_EQ(f(Integer(-5))->toString(), "-0.99990920426259513121");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.099667994624955817118");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.4621171572600097585");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "tanh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "tanh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(TanhTests, exprTest) {
  EXPECT_EQ(tanhExpr(Integer(10))->toString(), "tanh(10)");
}

TEST(TanhTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Tanh);
  EXPECT_EQ(f.getType(), MathObjectType::Tanh);
}
