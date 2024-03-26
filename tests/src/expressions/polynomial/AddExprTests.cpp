#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"

using namespace fintamath;

TEST(AddExprTests, getClassTest) {
  const auto expr = addExpr(Integer(0), Integer(0));

  EXPECT_EQ(expr->getClass(), MathObjectClass("AddExpr"));
  EXPECT_EQ(expr->getClass().getParent(), IPolynomExpression::getClassStatic());
}
