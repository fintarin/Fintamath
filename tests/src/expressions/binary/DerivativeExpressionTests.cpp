#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"

using namespace fintamath;

TEST(DerivativeExpressionTests, getTypeTest) {
  EXPECT_EQ(derivativeExpr(Integer(0), Integer(0))->getType(), MathObjectType::DerivativeExpression);
}
