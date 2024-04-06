#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"

using namespace fintamath;

TEST(TrigExprTests, getClassTest) {
  const auto expr = sinExpr(Integer(0).clone());

  EXPECT_EQ(expr->getClass()->getName(), "TrigExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IUnaryExpression::getClassStatic());
}
