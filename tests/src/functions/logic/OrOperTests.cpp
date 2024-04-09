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

  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call OrOper "|" with argument #0 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call OrOper "|" with argument #1 Integer "1" (expected Boolean))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call OrOper "|" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call OrOper "|" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call OrOper "|" with 3 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Boolean(true), Boolean(false)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call OrOper "|" with 4 arguments (expected 2))")));
}

TEST(OrOperTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "OrOper");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
