#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"

using namespace fintamath;

TEST(InvTrigExprTests, getClassTest) {
  const auto expr = asinExpr(Integer(0).clone());

  EXPECT_EQ(expr->getClass(), MathObjectClass("InvTrigExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IUnaryExpression::getClassStatic());
}
