#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/calculus/Max.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Max f;

TEST(MaxTests, toStringTest) {
  EXPECT_EQ(f.toString(), "max");
}

TEST(MaxTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IComparable::getClassStatic()));
}

TEST(MaxTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IComparable::getClassStatic());
}

TEST(MaxTests, isVariadicTest) {
  EXPECT_TRUE(f.isVariadic());
}

TEST(MaxTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(MaxTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1), Rational(-5, 2))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Rational(5, 2), Rational(-5, 2), Integer(-1))->toString(), "5/2");

  EXPECT_EQ(f(Integer(1), Rational(5, 2), Complex(1, 1))->toString(), "max(1, 5/2, 1 + I)");
  EXPECT_EQ(f(Integer(1), Complex(1, 1), Rational(5, 2))->toString(), "max(1, 1 + I, 5/2)");

  EXPECT_EQ(f(Rational(-1), Variable("x"), Variable("y"), Integer(1))->toString(), "max(x, y, 1)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer(), Integer()), InvalidInputFunctionException);
}

TEST(MaxTests, exprTest) {
  EXPECT_EQ(maxExpr(Variable("a"), Variable("a"))->toString(), "max(a, a)");
}

TEST(MaxTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Max"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
