#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Acoth f;

TEST(AcothTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acoth");
}

TEST(AcothTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AcothTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AcothTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AcothTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AcothTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "-Inf");
  EXPECT_EQ(f(Integer(0))->toString(), "(I Pi)/2");
  EXPECT_EQ(f(Integer(1))->toString(), "Inf");
  EXPECT_EQ(f(Integer(2))->toString(), "0.5493061443340548457");

  EXPECT_EQ(f(Rational(27, 10))->toString(), "0.38885228429400418206");
  EXPECT_EQ(f(Rational(23, 13))->toString(), "0.6404669227310321588");

  EXPECT_EQ(f(Real("1.5"))->toString(), "0.8047189562170501873");
  EXPECT_EQ(f(Real("0.5"))->toString(), "acoth(0.5)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "acoth(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "acoth(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acoth "acoth" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acoth "acoth" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acoth "acoth" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acoth "acoth" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Acoth "acoth" with 4 arguments (expected 1))")));
}

TEST(AcothTests, exprTest) {
  EXPECT_EQ(acothExpr(Integer(10))->toString(), "acoth(10)");
}

TEST(AcothTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Acoth");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
