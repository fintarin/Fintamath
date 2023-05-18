#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Integral.hpp"

using namespace fintamath;

TEST(IntegralExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Integral(), Integer(0).clone(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::IntegralExpression));
}
