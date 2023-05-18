#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"

using namespace fintamath;

TEST(TrigonometryExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Sin(), Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::TrigonometryExpression));
}
