#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"

using namespace fintamath;

TEST(DivExprTests, getClassTest) {
  const auto expr = divExpr(Integer(0), Integer(0));

  EXPECT_EQ(expr->getClass(), MathObjectClass("DivExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IBinaryExpression::getClassStatic());
}
