#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"

using namespace fintamath;

TEST(InvHyperbExprTests, getClassTest) {
  const auto expr = asinhExpr(Integer(0).clone());

  EXPECT_EQ(expr->getClass()->getName(), "InvHyperbExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IUnaryExpression::getClassStatic());
}
