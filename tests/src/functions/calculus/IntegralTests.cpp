#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/calculus/Integral.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Integral f;

TEST(IntegralTests, toStringTest) {
  EXPECT_EQ(f.toString(), "integral");
}

TEST(IntegralTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IComparable::getClassStatic(), Variable::getClassStatic()));
}

TEST(IntegralTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IComparable::getClassStatic());
}

TEST(IntegralTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(IntegralTests, isEvaluatableTest) {
  EXPECT_FALSE(f.isEvaluatable());
}

TEST(IntegralTests, callTest) {
  // TODO: integral
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "integral(a, a)");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "integral(a, b)");
  EXPECT_EQ(f(Expression("a+a"), Variable("a"))->toString(), "integral(2 a, a)");
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "integral(5, a)");

  EXPECT_THAT(
      [&] { f(Boolean(true), Variable("a")); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Integral "integral" with argument #0 Boolean "True" (expected IComparable))")));
  EXPECT_THAT(
      [&] { f(Variable("a"), Boolean(true)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Integral "integral" with argument #1 Boolean "True" (expected Variable))")));

  EXPECT_THAT(
      [&] { f(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Integral "integral" with 0 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Integral "integral" with 1 argument (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Integral "integral" with 3 arguments (expected 2))")));
  EXPECT_THAT(
      [&] { f(Integer(1), Integer(2), Integer(3), Integer(4)); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Unable to call Integral "integral" with 4 arguments (expected 2))")));
}

TEST(IntegralTests, exprTest) {
  EXPECT_EQ(integralExpr(Variable("a"), Variable("a"))->toString(), "integral(a, a)");
}

TEST(IntegralTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Integral");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
