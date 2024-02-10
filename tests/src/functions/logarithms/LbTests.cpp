#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Lb;
const F f;

TEST(LbTests, toStringTest) {
  EXPECT_EQ(f.toString(), "lb");
}

TEST(LbTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(LbTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(LbTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(LbTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(LbTests, callTest) {
  EXPECT_EQ(f(Integer(2))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(), "3.3219280948873623479");
  EXPECT_EQ(f(Integer(3))->toString(), "1.5849625007211561815");

  EXPECT_EQ(f(Rational(1, 16))->toString(), "-4");

  EXPECT_EQ(f(Integer(-10))->toString(), "log(2, -10)");

  EXPECT_EQ(f(Variable("a"))->toString(), "log(2, a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}

TEST(LbTests, exprTest) {
  EXPECT_EQ(lbExpr(Integer(10))->toString(), "log(2, 10)");
}

TEST(LbTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Lb);
  EXPECT_EQ(f.getType(), MathObjectType::Lb);
}
