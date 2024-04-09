#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Equiv.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Equiv f;

TEST(EquivTests, toStringTest) {
  EXPECT_EQ(f.toString(), "<->");
}

TEST(EquivTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic(), Boolean::getClassStatic()));
}

TEST(EquivTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(EquivTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(EquivTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(EquivTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Equivalence);
}

TEST(EquivTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(EquivTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "(~a & ~b) | (a & b)");

  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Equiv "<->" with argument #0 Integer "1" (expected Boolean))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Equiv "<->" with argument #1 Integer "1" (expected Boolean))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Equiv "<->" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Equiv "<->" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Equiv "<->" with 3 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Boolean(false), Boolean(true), Boolean(false)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Equiv "<->" with 4 arguments (expected 2))")));
}

TEST(EquivTests, exprTest) {
  EXPECT_EQ(equivExpr(Boolean(true), Boolean(false))->toString(), "(True & False) | (~True & ~False)");
}

TEST(EquivTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Equiv");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
