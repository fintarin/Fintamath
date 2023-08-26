#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"

using namespace fintamath;

TEST(DerivativeExpressionTests, getTypeIdTest) {
  EXPECT_EQ(derivativeExpr(Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::DerivativeExpression));
}
