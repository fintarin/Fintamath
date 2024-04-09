#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Lb f;

TEST(LbTests, toStringTest) {
  EXPECT_EQ(f.toString(), "lb");
}

TEST(LbTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(LbTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(LbTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(LbTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(LbTests, callTest) {
  EXPECT_EQ(f(Integer(2))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(), "3.3219280948873623479");
  EXPECT_EQ(f(Integer(3))->toString(), "1.5849625007211561815");

  EXPECT_EQ(f(Rational(1, 16))->toString(), "-4");

  EXPECT_EQ(f(Integer(-10))->toString(), "log(2, -10)");

  EXPECT_EQ(f(Variable("a"))->toString(), "log(2, a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Lb "lb" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Lb "lb" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Lb "lb" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Lb "lb" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Lb "lb" with 4 arguments (expected 1))")));
}

TEST(LbTests, exprTest) {
  EXPECT_EQ(lbExpr(Integer(10))->toString(), "log(2, 10)");
}

TEST(LbTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Lb");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
