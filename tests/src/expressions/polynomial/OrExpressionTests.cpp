#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/Or.hpp"

using namespace fintamath;

TEST(OrExpressionTests, getTypeIdTest) {
  EXPECT_EQ(orExpr(Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::OrExpression));
}
