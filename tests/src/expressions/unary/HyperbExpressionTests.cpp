#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"

using namespace fintamath;

TEST(HyperbExpressionTests, getTypeTest) {
  EXPECT_EQ(sinhExpr(Integer(0).clone())->getType(), MathObjectType(MathObjectType::HyperbExpression, "HyperbExpression"));
}
