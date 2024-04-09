#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Mul f;

TEST(MulTests, toStringTest) {
  EXPECT_EQ(f.toString(), "mul");
}

TEST(MulTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
}

TEST(MulTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(MulTests, isVariadicTest) {
  EXPECT_TRUE(f.isVariadic());
}

TEST(MulTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(MulTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Rational(1, 2))->toString(), "1/2");
  EXPECT_EQ(f(Real("0.333"))->toString(), "0.333");
  EXPECT_EQ(f(Complex(1, 2))->toString(), "1 + 2 I");
  EXPECT_EQ(f(Integer(13), Integer(56))->toString(), "728");
  EXPECT_EQ(f(Integer(33), Rational(4, 3))->toString(), "44");
  EXPECT_EQ(f(Rational(1, 2), Integer(10))->toString(), "5");
  EXPECT_EQ(f(Rational(1, 2), Rational(7, 2))->toString(), "7/4");
  EXPECT_EQ(f(Rational(1, 2), Rational(7, 3))->toString(), "7/6");
  EXPECT_EQ(f(Integer(1), Integer(1), Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Rational(1, 2), Integer(1), Real("0.5"))->toString(), "0.25");
  EXPECT_EQ(f(Complex(1, 2), Complex(Real(2), Rational(3, 2)), Rational(1, 2), Integer(1), Real("0.6"))->toString(), "-0.3 + 1.65 I");

  EXPECT_EQ(f(Variable("a"))->toString(), "a");
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "5 a");
  EXPECT_EQ(f(Variable("a"), Variable("a"), Variable("b"))->toString(), "a^2 b");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with argument #0 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with argument #1 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with argument #2 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with argument #3 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Boolean(true), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with argument #2 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Boolean(true), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with argument #1 Boolean "True" (expected IArithmetic))")));
  EXPECT_THAT(
      [&] { f(Boolean(true), Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with argument #0 Boolean "True" (expected IArithmetic))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Mul "mul" with 0 arguments (expected > 0))")));
}

TEST(MulTests, exprTest) {
  EXPECT_EQ(mulExpr(Integer(10), Integer(10))->toString(), "10*10");
}

TEST(MulTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Mul");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
