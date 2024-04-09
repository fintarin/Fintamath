#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sinh f;

TEST(SinhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sinh");
}

TEST(SinhTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(SinhTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(SinhTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(SinhTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(SinhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(5))->toString(), "74.203210577788758977");
  EXPECT_EQ(f(Integer(-5))->toString(), "-74.203210577788758977");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.10016675001984402582");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.52109530549374736162");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sinh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sinh(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sinh "sinh" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sinh "sinh" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sinh "sinh" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sinh "sinh" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Sinh "sinh" with 4 arguments (expected 1))")));
}

TEST(SinhTests, exprTest) {
  EXPECT_EQ(sinhExpr(Integer(10))->toString(), "sinh(10)");
}

TEST(SinhTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Sinh");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
