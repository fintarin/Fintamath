#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(AbsExprTests, getClassTest) {
  const auto expr = absExpr(Integer(0).clone());

  EXPECT_EQ(expr->getClass(), MathObjectClass("AbsExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IUnaryExpression::getClassStatic());
}
