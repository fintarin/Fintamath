#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Asin f;

TEST(AsinTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asin");
}

TEST(AsinTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AsinTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AsinTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AsinTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AsinTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/2");
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(-2))->toString(), "asin(-2)");
  EXPECT_EQ(f(Integer(2))->toString(), "asin(2)");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.10016742116155979635");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "-0.20135792079033079146");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.52359877559829887308");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asin(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asin(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asin "asin" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asin "asin" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asin "asin" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asin "asin" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asin "asin" with 4 arguments (expected 1))")));
}

TEST(AsinTests, exprTest) {
  EXPECT_EQ(asinExpr(Integer(10))->toString(), "asin(10)");
}

TEST(AsinTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Asin");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
