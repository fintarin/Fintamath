#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Index.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

const Index f;

TEST(IndexTests, toStringTest) {
  EXPECT_EQ(f.toString(), "_");
}

TEST(IndexTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Variable::getClassStatic(), Integer::getClassStatic()));
}

TEST(IndexTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Variable::getClassStatic());
}

TEST(IndexTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(IndexTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(IndexTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Exponentiation);
}

TEST(IndexTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(IndexTests, callTest) {
  EXPECT_EQ(f(Expression("a"), Integer(0))->toString(), "a_0");
  EXPECT_EQ(f(Variable("a"), Integer(1))->toString(), "a_1");
  EXPECT_EQ(f(Variable("a"), Integer(2))->toString(), "a_2");
  EXPECT_EQ(f(Variable("a"), Integer("100000000000000000000000000000000"))->toString(),
            "a_100000000000000000000000000000000");

  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Index "_" with argument #0 Boolean "True" (expected Variable))")));
  EXPECT_THAT(
      [&] { f(Variable("a"), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Index "_" with argument #1 Boolean "True" (expected Integer))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Index "_" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Index "_" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Index "_" with 3 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Index "_" with 4 arguments (expected 2))")));
}

TEST(IndexTests, exprTest) {
  EXPECT_EQ(indexExpr(Variable("a"), Integer(1))->toString(), "a_1");
}

TEST(IndexTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Index");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
