#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acosh f;

TEST(AcoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acosh");
}

TEST(AcoshTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AcoshTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AcoshTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcoshTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcoshTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "I Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "(I Pi)/2");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(), "1.3169578969248167086");
  EXPECT_EQ(f(Integer(-2))->toString(), "acosh(-2)");

  EXPECT_EQ(f(Rational(11, 10))->toString(), "0.44356825438511518913");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "1.1720930632462197633");

  EXPECT_EQ(f(Real("1.5"))->toString(), "0.962423650119206895");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acosh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acosh(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acosh "acosh" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acosh "acosh" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acosh "acosh" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acosh "acosh" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acosh "acosh" with 4 arguments (expected 1))")));
}

TEST(AcoshTests, exprTest) {
  EXPECT_EQ(acoshExpr(Integer(10))->toString(), "acosh(10)");
}

TEST(AcoshTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Acosh");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
