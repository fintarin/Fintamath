#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"

using namespace fintamath;

TEST(InvTrigExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Asin(), Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::InvTrigExpression));
}
