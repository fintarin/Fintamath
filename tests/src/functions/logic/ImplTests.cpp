#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Impl.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Impl f;

TEST(ImplTests, toStringTest) {
  EXPECT_EQ(f.toString(), "->");
}

TEST(ImplTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic(), Boolean::getClassStatic()));
}

TEST(ImplTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(ImplTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(ImplTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(ImplTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Implication);
}

TEST(ImplTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(ImplTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "~a | b");

  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Impl "->" with argument #0 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Impl "->" with argument #1 Integer "1" (expected Boolean))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Impl "->" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Impl "->" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Impl "->" with 3 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Boolean(true), Boolean(false)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Impl "->" with 4 arguments (expected 2))")));
}

TEST(ImplTests, exprTest) {
  EXPECT_EQ(implExpr(Boolean(true), Boolean(false))->toString(), "~True | False");
}

TEST(ImplTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Impl");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
