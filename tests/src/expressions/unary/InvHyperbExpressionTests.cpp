#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"

using namespace fintamath;

TEST(InvHyperbExpressionTests, getTypeTest) {
  EXPECT_EQ(asinhExpr(Integer(0).clone())->getType(), MathObjectType::InvHyperbExpression);
}
