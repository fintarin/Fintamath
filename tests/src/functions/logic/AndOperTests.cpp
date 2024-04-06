#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/AndOper.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const AndOper f;

TEST(AndOperTests, toStringTest) {
  EXPECT_EQ(f.toString(), "&");
}

TEST(AndOperTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic(), Boolean::getClassStatic()));
}

TEST(AndOperTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(AndOperTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AndOperTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AndOperTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Conjunction);
}

TEST(AndOperTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(AndOperTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a & b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(AndOperTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "AndOper");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
