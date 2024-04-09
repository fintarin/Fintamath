#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Cosh f;

TEST(CoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cosh");
}

TEST(CoshTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(CoshTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(CoshTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(CoshTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CoshTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(5))->toString(), "74.209948524787844444");
  EXPECT_EQ(f(Integer(-5))->toString(), "74.209948524787844444");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "1.005004168055803599");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.1276259652063807852");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "cosh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "cosh(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cosh "cosh" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cosh "cosh" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cosh "cosh" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cosh "cosh" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cosh "cosh" with 4 arguments (expected 1))")));
}

TEST(CoshTests, exprTest) {
  EXPECT_EQ(coshExpr(Integer(10))->toString(), "cosh(10)");
}

TEST(CoshTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Cosh");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
