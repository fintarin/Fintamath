#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"

using namespace fintamath;

TEST(HyperbExprTests, getClassTest) {
  const auto expr = sinhExpr(Integer(0).clone());

  EXPECT_EQ(expr->getClass(), MathObjectClass("HyperbExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IUnaryExpression::getClassStatic());
}
