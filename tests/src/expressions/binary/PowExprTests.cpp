#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/powers/Pow.hpp"

using namespace fintamath;

TEST(PowExprTests, getClassTest) {
  const auto expr = powExpr(Integer(0), Integer(0));

  EXPECT_EQ(expr->getClass(), MathObjectClass("PowExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IBinaryExpression::getClassStatic());
}
