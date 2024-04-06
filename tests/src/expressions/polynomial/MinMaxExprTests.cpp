#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/calculus/Min.hpp"

using namespace fintamath;

TEST(MinMaxExprTests, getClassTest) {
  const auto expr = minExpr(Integer(0), Integer(0));

  EXPECT_EQ(expr->getClass()->getName(), "MinMaxExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IPolynomExpression::getClassStatic());
}
