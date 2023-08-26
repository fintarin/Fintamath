#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"

using namespace fintamath;

TEST(HyperbExpressionTests, getTypeIdTest) {
  EXPECT_EQ(sinhExpr(Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::HyperbExpression));
}
