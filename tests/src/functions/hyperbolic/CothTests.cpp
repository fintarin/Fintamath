#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Coth.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Coth f;

TEST(CothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "coth");
}

TEST(CothTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(CothTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(CothTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(CothTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CothTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(5))->toString(), "1.0000908039820193755");
  EXPECT_EQ(f(Integer(-5))->toString(), "-1.0000908039820193755");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "10.03331113225398961");
  EXPECT_EQ(f(Rational(11, 10))->toString(), "1.2492207645683124166");

  EXPECT_EQ(f(Real("0.5"))->toString(), "2.1639534137386528488");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "coth(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "coth(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Coth "coth" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Coth "coth" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Coth "coth" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Coth "coth" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Coth "coth" with 4 arguments (expected 1))")));
}

TEST(CothTests, exprTest) {
  EXPECT_EQ(cothExpr(Integer(10))->toString(), "coth(10)");
}

TEST(CothTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Coth");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
