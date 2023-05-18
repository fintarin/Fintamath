#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"

using namespace fintamath;

TEST(DerivativeExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Derivative(), Integer(0).clone(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::DerivativeExpression));
}
