#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/logarithms/Log.hpp"

using namespace fintamath;

TEST(LogExprTests, getClassTest) {
  const auto expr = logExpr(Integer(0), Integer(0));

  EXPECT_EQ(expr->getClass()->getName(), "LogExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IBinaryExpression::getClassStatic());
}
