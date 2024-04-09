#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/ntheory/Floor.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Floor f;

TEST(FloorTests, toStringTest) {
  EXPECT_EQ(f.toString(), "floor");
}

TEST(FloorTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(FloorTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(FloorTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(FloorTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(FloorTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "10");
  EXPECT_EQ(f(Integer(-10))->toString(), "-10");

  EXPECT_EQ(f(Rational("-2.9"))->toString(), "-3");
  EXPECT_EQ(f(Rational("-2.2"))->toString(), "-3");
  EXPECT_EQ(f(Rational("-2"))->toString(), "-2");
  EXPECT_EQ(f(Rational("0"))->toString(), "0");
  EXPECT_EQ(f(Rational("2"))->toString(), "2");
  EXPECT_EQ(f(Rational("2.2"))->toString(), "2");
  EXPECT_EQ(f(Rational("2.9"))->toString(), "2");

  EXPECT_EQ(f(Real("-2.9"))->toString(), "-3");
  EXPECT_EQ(f(Real("-2.2"))->toString(), "-3");
  EXPECT_EQ(f(Real("-2"))->toString(), "floor(-2.0)");
  EXPECT_EQ(f(Real("0"))->toString(), "floor(0.0)");
  EXPECT_EQ(f(Real("2"))->toString(), "floor(2.0)");
  EXPECT_EQ(f(Real("2.2"))->toString(), "2");
  EXPECT_EQ(f(Real("2.9"))->toString(), "2");

  EXPECT_EQ(f(Complex(0, 0))->toString(), "0");
  EXPECT_EQ(f(Complex(2, 0))->toString(), "2");
  EXPECT_EQ(f(Complex(0, 2))->toString(), "2 I");
  EXPECT_EQ(f(Complex(2, 2))->toString(), "2 + 2 I");
  EXPECT_EQ(f(Complex(Rational("1.1"), Rational("2.2")))->toString(), "1 + 2 I");
  EXPECT_EQ(f(Complex(Rational("1.1"), Rational("-2.2")))->toString(), "1 - 3 I");
  EXPECT_EQ(f(Complex(Rational("-1.1"), Rational("2.2")))->toString(), "-2 + 2 I");
  EXPECT_EQ(f(Complex(Rational("-1.1"), Rational("-2.2")))->toString(), "-2 - 3 I");
  EXPECT_EQ(f(Complex(Real("1.1"), Real("2.2")))->toString(), "1 + 2 I");
  EXPECT_EQ(f(Complex(Real("1.1"), Real("-2.2")))->toString(), "1 - 3 I");
  EXPECT_EQ(f(Complex(Real("-1.1"), Real("2.2")))->toString(), "-2 + 2 I");
  EXPECT_EQ(f(Complex(Real("-1.1"), Real("-2.2")))->toString(), "-2 - 3 I");
  EXPECT_EQ(f(Complex(Real("0"), Real("0")))->toString(), "floor(0.0 + 0.0 I)");
  EXPECT_EQ(f(Complex(Real("0"), Real("0.5")))->toString(), "floor(0.0 + 0.5 I)");
  EXPECT_EQ(f(Complex(Real("0.5"), Real("0")))->toString(), "floor(0.5 + 0.0 I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "floor(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Floor "floor" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Floor "floor" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Floor "floor" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Floor "floor" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Floor "floor" with 4 arguments (expected 1))")));
}

TEST(FloorTests, exprTest) {
  EXPECT_EQ(floorExpr(Integer(10))->toString(), "floor(10)");
}

TEST(FloorTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Floor");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
