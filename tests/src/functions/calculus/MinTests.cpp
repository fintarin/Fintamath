#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/calculus/Min.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Min;
const F f;

TEST(MinTests, toStringTest) {
  EXPECT_EQ(f.toString(), "min");
}

TEST(MinTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IComparable::getTypeStatic()));
}

TEST(MinTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IComparable::getTypeStatic());
}

TEST(MinTests, isVariadicTest) {
  EXPECT_TRUE(F::isVariadicStatic());
  EXPECT_TRUE(f.isVariadic());
}

TEST(MinTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(MinTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1))->toString(), "-1");
  EXPECT_EQ(f(Integer(1), Integer(-1), Rational(-5, 2))->toString(), "-5/2");
  EXPECT_EQ(f(Integer(1), Rational(5, 2), Rational(-5, 2), Integer(-1))->toString(), "-5/2");

  EXPECT_EQ(f(Integer(1), Rational(5, 2), Complex(1, 1))->toString(), "min(1, 5/2, 1 + I)");
  EXPECT_EQ(f(Integer(1), Complex(1, 1), Rational(5, 2))->toString(), "min(1, 1 + I, 5/2)");

  EXPECT_EQ(f(Rational(-1), Variable("x"), Variable("y"), Integer(1))->toString(), "min(x, y, -1)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer(), Integer()), InvalidInputFunctionException);
}

TEST(MinTests, exprTest) {
  EXPECT_EQ(minExpr(Variable("a"), Variable("a"))->toString(), "min(a, a)");
}

TEST(MinTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Min);
  EXPECT_EQ(f.getType(), MathObjectType::Min);
}
