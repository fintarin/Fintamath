#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"

using namespace fintamath;

TEST(CompExprTests, getClassTest) {
  const auto expr = eqvExpr(Integer(0), Integer(0));

  EXPECT_EQ(expr->getClass(), MathObjectClass("CompExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IBinaryExpression::getClassStatic());
}
