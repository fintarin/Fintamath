#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/logic/Or.hpp"

using namespace fintamath;

TEST(OrExprTests, getClassTest) {
  const auto expr = orExpr(Boolean(), Boolean());

  EXPECT_EQ(expr->getClass(), MathObjectClass("OrExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IPolynomExpression::getClassStatic());
}
