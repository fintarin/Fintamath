#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Or.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Or f;

TEST(OrTests, toStringTest) {
  EXPECT_EQ(f.toString(), "|");
}

TEST(OrTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic(), Boolean::getClassStatic()));
}

TEST(OrTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(OrTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(OrTests, isEvaluatableTest) {
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

TEST(OrTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Or"));
  EXPECT_EQ(f.getClass().getParent(), IOperator::getClassStatic());
}
