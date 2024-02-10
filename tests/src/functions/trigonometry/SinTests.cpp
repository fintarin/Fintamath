#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

using F = Sin;
const F f;

TEST(SinTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sin");
}

TEST(SinTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(SinTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(SinTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(SinTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SinTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "-0.5440211108893698134");
  EXPECT_EQ(f(Integer(5))->toString(), "-0.95892427466313846889");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.099833416646828152307");

  EXPECT_EQ(f(Real("1.123"))->toString(), "0.90140343710581305144");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sin(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sin(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SinTests, exprTest) {
  EXPECT_EQ(sinExpr(Integer(10))->toString(), "sin(10)");
}

TEST(SinTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Sin);
  EXPECT_EQ(f.getType(), MathObjectType::Sin);
}
