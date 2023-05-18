#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"

using namespace fintamath;

TEST(FunctionExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Abs(), Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::FunctionExpression));
}
