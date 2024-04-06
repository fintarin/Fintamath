#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/logic/Not.hpp"

using namespace fintamath;

TEST(NotExprTests, getClassTest) {
  const auto expr = notExpr(Boolean());

  EXPECT_EQ(expr->getClass()->getName(), "NotExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IUnaryExpression::getClassStatic());
}
