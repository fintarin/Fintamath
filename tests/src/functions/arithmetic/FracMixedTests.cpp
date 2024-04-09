#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/FracMixed.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const FracMixed f;

TEST(FracMixedTests, toStringTest) {
  EXPECT_EQ(f.toString(), "frac");
}

TEST(FracMixedTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic(), IArithmetic::getClassStatic(), IArithmetic::getClassStatic()));
}

TEST(FracMixedTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(FracMixedTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(FracMixedTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(FracMixedTests, callTest) {
  EXPECT_EQ(f(Integer(0), Integer(3), Integer(5))->toString(), "3/5");
  EXPECT_EQ(f(Integer(0), Integer(3), Rational(5, 2))->toString(), "6/5");
  EXPECT_EQ(f(Integer(0), Rational(5, 2), Integer(3))->toString(), "5/6");
  EXPECT_EQ(f(Integer(0), Rational(-5, 2), Rational(5, 3))->toString(), "-3/2");
  EXPECT_EQ(f(Integer(2), Integer(3), Integer(5))->toString(), "13/5");
  EXPECT_EQ(f(Integer(2), Integer(3), Integer(-5))->toString(), "7/5");
  EXPECT_EQ(f(Integer(2), Integer(-3), Integer(5))->toString(), "7/5");
  EXPECT_EQ(f(Integer(-2), Integer(3), Integer(5))->toString(), "-7/5");
  EXPECT_EQ(f(Integer(-5), Integer(3), Rational(5, 2))->toString(), "-19/5");
  EXPECT_EQ(f(Integer(14), Rational(-5, 2), Integer(-3))->toString(), "89/6");
  EXPECT_EQ(f(Integer(-12), Rational(15, 5), Rational(5, -3))->toString(), "-69/5");

  EXPECT_EQ(f(Integer(0), Integer(3), Variable("a"))->toString(), "3/a");

  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call FracMixed "frac" with argument #2 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call FracMixed "frac" with argument #1 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call FracMixed "frac" with argument #0 Boolean "True" (expected IArithmetic))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call FracMixed "frac" with 0 arguments (expected 3))")));
  EXPECT_THAT(
      [&] { f(Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call FracMixed "frac" with 1 argument (expected 3))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call FracMixed "frac" with 2 arguments (expected 3))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call FracMixed "frac" with 4 arguments (expected 3))")));
}

TEST(FracMixedTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "FracMixed");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
