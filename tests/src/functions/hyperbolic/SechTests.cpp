#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Sech.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sech f;

TEST(SechTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sech");
}

TEST(SechTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(SechTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(SechTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(SechTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SechTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(5))->toString(), "0.013475282221304557306");
  EXPECT_EQ(f(Integer(-5))->toString(), "0.013475282221304557306");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.99502074895322649163");
  EXPECT_EQ(f(Rational(11, 10))->toString(), "0.59933406057079292981");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.88681888397007390866");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sech(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sech(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sech "sech" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sech "sech" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sech "sech" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sech "sech" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sech "sech" with 4 arguments (expected 1))")));
}

TEST(SechTests, exprTest) {
  EXPECT_EQ(sechExpr(Integer(10))->toString(), "sech(10)");
}

TEST(SechTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Sech");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
