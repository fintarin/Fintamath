#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Asec.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Asec f;

TEST(AsecTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asec");
}

TEST(AsecTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(AsecTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(AsecTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AsecTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AsecTests, callTest) {
  EXPECT_EQ(f(Integer(-1))->toString(), "Pi");
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(-2))->toString(), "2.0943951023931954923");
  EXPECT_EQ(f(Integer(2))->toString(), "1.0471975511965977462");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "asec(1/10)");
  EXPECT_EQ(f(Rational(-1, 5))->toString(), "asec(-1/5)");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "asec(0.5)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "asec(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "asec(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asec "asec" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asec "asec" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asec "asec" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asec "asec" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Asec "asec" with 4 arguments (expected 1))")));
}

TEST(AsecTests, exprTest) {
  EXPECT_EQ(asecExpr(Integer(10))->toString(), "asec(10)");
}

TEST(AsecTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Asec");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
