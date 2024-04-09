#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Neg.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Neg f;

TEST(NegTests, toStringTest) {
  EXPECT_EQ(f.toString(), "-");
}

TEST(NegTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
}

TEST(NegTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(NegTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(NegTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(NegTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PrefixUnary);
}

TEST(NegTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(NegTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "-3");
  EXPECT_EQ(f(Rational(5, 2))->toString(), "-5/2");
  EXPECT_EQ(f(Rational(-5, 2))->toString(), "5/2");

  EXPECT_EQ(f(Variable("a"))->toString(), "-a");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Neg "-" with argument #0 Boolean "True" (expected IArithmetic))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Neg "-" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Neg "-" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Neg "-" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Neg "-" with 4 arguments (expected 1))")));
}

TEST(NegTests, exprTest) {
  EXPECT_EQ(negExpr(Integer(10))->toString(), "-10");
}

TEST(NegTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Neg");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
