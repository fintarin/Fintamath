#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Acsc.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acsc f;

TEST(AcscTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acsc");
}

TEST(AcscTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AcscTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AcscTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcscTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcscTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/2");
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(-2))->toString(), "-0.52359877559829887308");
  EXPECT_EQ(f(Integer(2))->toString(), "0.52359877559829887308");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "acsc(1/10)");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "acsc(-1/5)");

  EXPECT_EQ(f(Real("0.5"))->toString(), "acsc(0.5)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acsc(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acsc(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsc "acsc" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsc "acsc" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsc "acsc" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsc "acsc" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsc "acsc" with 4 arguments (expected 1))")));
}

TEST(AcscTests, exprTest) {
  EXPECT_EQ(acscExpr(Integer(10))->toString(), "acsc(10)");
}

TEST(AcscTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Acsc");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
