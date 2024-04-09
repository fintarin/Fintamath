#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Sub.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Sub f;

TEST(SubTests, toStringTest) {
  EXPECT_EQ(f.toString(), "-");
}

TEST(SubTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic(), IArithmetic::getClassStatic()));
}

TEST(SubTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(SubTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(SubTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SubTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Addition);
}

TEST(SubTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(SubTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "-2");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "1/2");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "-1/2");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 2))->toString(), "0");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "5/6");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "-a + 3");

  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sub "-" with argument #0 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sub "-" with argument #1 Boolean "True" (expected IArithmetic))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sub "-" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sub "-" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sub "-" with 3 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sub "-" with 4 arguments (expected 2))")));
}

TEST(SubTests, exprTest) {
  EXPECT_EQ(subExpr(Integer(10), Integer(10))->toString(), "10 - 10");
}

TEST(SubTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Sub");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
