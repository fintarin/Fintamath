#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/And.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const And f;

TEST(AndTests, toStringTest) {
  EXPECT_EQ(f.toString(), "and");
}

TEST(AndTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic()));
}

TEST(AndTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(AndTests, isVariadicTest) {
  EXPECT_TRUE(f.isVariadic());
}

TEST(AndTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AndTests, callTest) {
  EXPECT_EQ(f(Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(false), Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true), Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false), Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true), Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"))->toString(), "a");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a & b");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Variable("c"))->toString(), "a & b & c");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Variable("a"), Variable("c"))->toString(), "a & b & c");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Variable("b"), Variable("a"))->toString(), "a & b");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Boolean("True"), Variable("c"))->toString(), "a & b & c");
  EXPECT_EQ(f(Boolean("False"), Variable("a"), Variable("b"), Variable("c"))->toString(), "False");

  EXPECT_THAT(
      [&] { f(Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with argument #0 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with argument #1 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with argument #2 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Boolean(true), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with argument #3 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Integer(1), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with argument #2 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1), Boolean(false), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with argument #1 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true), Boolean(false), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with argument #0 Integer "1" (expected Boolean))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call And "and" with 0 arguments (expected > 0))")));
}

TEST(AndTests, exprTest) {
  EXPECT_EQ(andExpr(Boolean(true), Boolean(false))->toString(), "True & False");
}

TEST(AndTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "And");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
