#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/OrOper.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const OrOper f;

TEST(OrOperTests, toStringTest) {
  EXPECT_EQ(f.toString(), "|");
}

TEST(OrOperTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic(), Boolean::getClassStatic()));
}

TEST(OrOperTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(OrOperTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(OrOperTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(OrOperTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Disjunction);
}

TEST(OrOperTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(OrOperTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a | b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(OrOperTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("OrOper"));
  EXPECT_EQ(f.getClass().getParent(), IOperator::getClassStatic());
}
