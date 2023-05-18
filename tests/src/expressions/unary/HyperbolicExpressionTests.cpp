#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"

using namespace fintamath;

TEST(HyperbolicExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Sinh(), Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::HyperbolicExpression));
}
