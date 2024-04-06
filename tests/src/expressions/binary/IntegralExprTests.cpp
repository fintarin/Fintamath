#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/calculus/Integral.hpp"

using namespace fintamath;

TEST(IntegralExprTests, getClassTest) {
  const auto expr = integralExpr(Integer(0), Variable("x"));

  EXPECT_EQ(expr->getClass()->getName(), "IntegralExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IBinaryExpression::getClassStatic());
}
