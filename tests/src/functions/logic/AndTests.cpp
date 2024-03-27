#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/And.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const And f;

TEST(AndTests, toStringTest) {
  EXPECT_EQ(f.toString(), "&");
}

TEST(AndTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic(), Boolean::getClassStatic()));
}

TEST(AndTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(AndTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AndTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AndTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Conjunction);
}

TEST(AndTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(AndTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a & b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(AndTests, exprTest) {
  EXPECT_EQ(andExpr(Boolean(true), Boolean(false))->toString(), "True & False");
}

TEST(AndTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("And"));
  EXPECT_EQ(f.getClass().getParent(), IOperator::getClassStatic());
}
