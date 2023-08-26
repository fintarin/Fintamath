#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"

using namespace fintamath;

TEST(InvHyperbExpressionTests, getTypeIdTest) {
  EXPECT_EQ(asinhExpr(Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::InvHyperbExpression));
}
