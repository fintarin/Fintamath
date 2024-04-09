#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acot f;

TEST(AcotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acot");
}

TEST(AcotTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AcotTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AcotTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcotTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcotTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Pi/4");
  EXPECT_EQ(f(Integer(0))->toString(), "Pi/2");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/4");
  EXPECT_EQ(f(Integer(-2))->toString(), "-0.46364760900080611621");
  EXPECT_EQ(f(Integer(2))->toString(), "0.46364760900080611621");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "1.4711276743037345919");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "-1.3734007669450158609");

  EXPECT_EQ(f(Real("0.5"))->toString(), "1.107148717794090503");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acot(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acot(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acot "acot" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acot "acot" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acot "acot" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acot "acot" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acot "acot" with 4 arguments (expected 1))")));
}

TEST(AcotTests, exprTest) {
  EXPECT_EQ(acotExpr(Integer(10))->toString(), "acot(10)");
}

TEST(AcotTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Acot");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
