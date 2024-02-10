#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Or.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

using F = Or;
const F f;

TEST(OrTests, toStringTest) {
  EXPECT_EQ(f.toString(), "|");
}

TEST(OrTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(Boolean::getTypeStatic(), Boolean::getTypeStatic()));
}

TEST(OrTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), Boolean::getTypeStatic());
}

TEST(OrTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(OrTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(OrTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Disjunction);
}

TEST(OrTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(OrTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a | b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(OrTests, exprTest) {
  EXPECT_EQ(orExpr(Boolean(true), Boolean(false))->toString(), "True | False");
}

TEST(OrTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Or);
  EXPECT_EQ(f.getType(), MathObjectType::Or);
}
