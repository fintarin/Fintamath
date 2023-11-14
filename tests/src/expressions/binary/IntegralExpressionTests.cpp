#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Integral.hpp"

using namespace fintamath;

TEST(IntegralExpressionTests, getTypeTest) {
  EXPECT_EQ(integralExpr(Integer(0), Variable("x"))->getType(), MathObjectType::IntegralExpression);
}
