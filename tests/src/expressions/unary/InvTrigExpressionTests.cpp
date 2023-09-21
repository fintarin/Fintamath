#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"

using namespace fintamath;

TEST(InvTrigExpressionTests, getTypeTest) {
  EXPECT_EQ(asinExpr(Integer(0).clone())->getType(), MathObjectType::InvTrigExpression);
}
