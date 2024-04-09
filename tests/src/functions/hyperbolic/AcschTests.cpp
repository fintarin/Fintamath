#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Acsch.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acsch f;

TEST(AcschTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acsch");
}

TEST(AcschTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AcschTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AcschTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcschTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcschTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-0.88137358701954302523");
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(), "0.88137358701954302523");
  EXPECT_EQ(f(Integer(2))->toString(), "0.4812118250596034475");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "2.9982229502979697388");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "-2.3124383412727526203");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.4436354751788103425");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acsch(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acsch(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsch "acsch" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsch "acsch" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsch "acsch" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsch "acsch" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acsch "acsch" with 4 arguments (expected 1))")));
}

TEST(AcschTests, exprTest) {
  EXPECT_EQ(acschExpr(Integer(10))->toString(), "acsch(10)");
}

TEST(AcschTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Acsch");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
