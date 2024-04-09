#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Comma.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

const Comma f;

TEST(CommaTests, toStringTest) {
  EXPECT_EQ(f.toString(), ",");
}

TEST(CommaTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IMathObject::getClassStatic(), IMathObject::getClassStatic()));
}

TEST(CommaTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IMathObject::getClassStatic());
}

TEST(CommaTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(CommaTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CommaTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Comma);
}

TEST(CommaTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(CommaTests, callTest) {
  EXPECT_THAT(
      [&] { f(Variable("a"), Variable("a")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Calling Comma directly is not allowed)")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Comma "," with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Comma "," with 1 argument (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Comma "," with 3 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Comma "," with 4 arguments (expected 2))")));
}

TEST(CommaTests, exprTest) {
  EXPECT_EQ(commaExpr(Variable("a"), Integer(1))->toString(), "a , 1");
}

TEST(CommaTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Comma");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
