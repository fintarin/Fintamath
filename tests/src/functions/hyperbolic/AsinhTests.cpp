#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Asinh.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Asinh f;

TEST(AsinhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asinh");
}

TEST(AsinhTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AsinhTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AsinhTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AsinhTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AsinhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "0.88137358701954302523");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.099834078899207563327");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "-0.19869011034924140647");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.4812118250596034475");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asinh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asinh(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asinh "asinh" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asinh "asinh" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asinh "asinh" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asinh "asinh" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asinh "asinh" with 4 arguments (expected 1))")));
}

TEST(AsinhTests, exprTest) {
  EXPECT_EQ(asinhExpr(Integer(10))->toString(), "asinh(10)");
}

TEST(AsinhTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Asinh");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
