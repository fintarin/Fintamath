#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Percent f;

TEST(PercentTests, toStringTest) {
  EXPECT_EQ(f.toString(), "%");
}

TEST(PercentTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(PercentTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(PercentTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(PercentTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(PercentTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PostfixUnary);
}

TEST(PercentTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(PercentTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1/100");
  EXPECT_EQ(f(Integer(1000))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "-1/10");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "1/1000");

  EXPECT_EQ(f(Variable("a"))->toString(), "a/100");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(PercentTests, degTest) {
  EXPECT_EQ(percentExpr(Integer(10))->toString(), "10/100");
}

TEST(PercentTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Percent"));
  EXPECT_EQ(f.getClass().getParent(), IOperator::getClassStatic());
}
