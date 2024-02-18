#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/calculus/Integral.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Integral;
const F f;

TEST(IntegralTests, toStringTest) {
  EXPECT_EQ(f.toString(), "integral");
}

TEST(IntegralTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IComparable::getTypeStatic(), Variable::getTypeStatic()));
}

TEST(IntegralTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IComparable::getTypeStatic());
}

TEST(IntegralTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(IntegralTests, isEvaluatableTest) {
  EXPECT_FALSE(F::isEvaluatableStatic());
  EXPECT_FALSE(f.isEvaluatable());
}

TEST(IntegralTests, callTest) {
  // TODO: integral
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "integral(a, a)");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "integral(a, b)");
  EXPECT_EQ(f(Expression("a+a"), Variable("a"))->toString(), "integral(2 a, a)");
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "integral(5, a)");

  EXPECT_THROW(f(Integer(5), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Expression("a+a")), InvalidInputException);

  EXPECT_THROW(f(), InvalidInputException);
  EXPECT_THROW(f(Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputException);
}

TEST(IntegralTests, exprTest) {
  EXPECT_EQ(integralExpr(Variable("a"), Variable("a"))->toString(), "integral(a, a)");
}

TEST(IntegralTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Integral, "Integral"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Integral, "Integral"));
}
