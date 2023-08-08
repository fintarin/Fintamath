#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"

using namespace fintamath;

TEST(InvHyperbolicExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Asinh(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::InvHyperbolicExpression));
}
