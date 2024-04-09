#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const UnaryPlus f;

TEST(UnaryPlusTests, toStringTest) {
  EXPECT_EQ(f.toString(), "+");
}

TEST(UnaryPlusTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
}

TEST(UnaryPlusTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(UnaryPlusTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(UnaryPlusTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(UnaryPlusTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PrefixUnary);
}

TEST(UnaryPlusTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(UnaryPlusTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "3");
  EXPECT_EQ(f(Rational(5, 2))->toString(), "5/2");
  EXPECT_EQ(f(Rational(-5, 2))->toString(), "-5/2");

  EXPECT_EQ(f(Variable("a"))->toString(), "a");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call UnaryPlus "+" with argument #0 Boolean "True" (expected IArithmetic))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call UnaryPlus "+" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call UnaryPlus "+" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call UnaryPlus "+" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call UnaryPlus "+" with 4 arguments (expected 1))")));
}

TEST(UnaryPlusTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "UnaryPlus");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
