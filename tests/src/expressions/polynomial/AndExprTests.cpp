#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(AndExprTests, getClassTest) {
  const auto expr = andExpr(Boolean(), Boolean());

  EXPECT_EQ(expr->getClass(), MathObjectClass("AndExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IPolynomExpression::getClassStatic());
}
