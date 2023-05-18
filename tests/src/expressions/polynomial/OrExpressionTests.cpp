#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/Or.hpp"

using namespace fintamath;

TEST(OrExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Or(), Integer(0).clone(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::OrExpression));
}
