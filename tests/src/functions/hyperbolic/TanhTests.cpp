#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/hyperbolic/Tanh.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Tanh f;

TEST(TanhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "tanh");
}

TEST(TanhTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(TanhTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(TanhTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(TanhTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(TanhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(5))->toString(), "0.99990920426259513121");
  EXPECT_EQ(f(Integer(-5))->toString(), "-0.99990920426259513121");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "0.099667994624955817118");

  EXPECT_EQ(f(Real("0.5"))->toString(), "0.4621171572600097585");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "tanh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "tanh(a)");

  EXPECT_THAT(
      [&] { f(Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Tanh "tanh" with argument #0 Boolean "True" (expected INumber))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Tanh "tanh" with 0 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Tanh "tanh" with 2 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Tanh "tanh" with 3 arguments (expected 1))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Tanh "tanh" with 4 arguments (expected 1))")));
}

TEST(TanhTests, exprTest) {
  EXPECT_EQ(tanhExpr(Integer(10))->toString(), "tanh(10)");
}

TEST(TanhTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Tanh");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
