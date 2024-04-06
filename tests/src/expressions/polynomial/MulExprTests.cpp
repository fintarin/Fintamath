#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"

using namespace fintamath;

TEST(MulExprTests, getClassTest) {
  const auto expr = mulExpr(Integer(0), Integer(0));

  EXPECT_EQ(expr->getClass()->getName(), "MulExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IPolynomExpression::getClassStatic());
}
