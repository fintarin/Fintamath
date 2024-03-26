#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"

using namespace fintamath;

TEST(DerivativeExprTests, getClassTest) {
  const auto expr = derivativeExpr(Integer(0), Variable("x"));

  EXPECT_EQ(expr->getClass(), MathObjectClass("DerivativeExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IBinaryExpression::getClassStatic());
}
