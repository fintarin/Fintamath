#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/powers/Sqr.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sqr f;

TEST(SqrTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sqr");
}

TEST(SqrTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(SqrTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(SqrTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(SqrTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SqrTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(100))->toString(), "10000");
  EXPECT_EQ(f(Integer(-100))->toString(), "10000");

  EXPECT_EQ(f(Rational(3, 5))->toString(), "9/25");

  EXPECT_EQ(f(Real("144.23"))->toString(), "20802.2929");

  EXPECT_EQ(f(Variable("a"))->toString(), "a^2");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SqrTests, exprTest) {
  EXPECT_EQ(sqrExpr(Integer(10))->toString(), "10^2");
}

TEST(SqrTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Sqr"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
