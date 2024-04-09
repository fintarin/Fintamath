#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Cot f;

TEST(CotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cot");
}

TEST(CotTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(CotTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(CotTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(CotTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CotTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(10))->toString(), "1.5423510453569200483");
  EXPECT_EQ(f(Integer(-10))->toString(), "-1.5423510453569200483");
  EXPECT_EQ(f(Integer(5))->toString(), "-0.29581291553274554043");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "9.9666444232592378598");

  EXPECT_EQ(f(Real("1.123"))->toString(), "0.48034006817334639693");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "cot(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "cot(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cot "cot" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cot "cot" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cot "cot" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cot "cot" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Cot "cot" with 4 arguments (expected 1))")));
}

TEST(CotTests, exprTest) {
  EXPECT_EQ(cotExpr(Integer(10))->toString(), "cot(10)");
}

TEST(CotTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Cot");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
