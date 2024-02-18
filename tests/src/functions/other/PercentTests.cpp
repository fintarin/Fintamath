#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Percent.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Percent;
const F f;

TEST(PercentTests, toStringTest) {
  EXPECT_EQ(f.toString(), "%");
}

TEST(PercentTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(PercentTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(PercentTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(PercentTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(PercentTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::PostfixUnary);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PostfixUnary);
}

TEST(PercentTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
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

TEST(PercentTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Percent, "Percent"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Percent, "Percent"));
}
