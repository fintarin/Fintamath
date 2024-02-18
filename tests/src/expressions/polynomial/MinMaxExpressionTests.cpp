#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Min.hpp"

using namespace fintamath;

TEST(MinMaxExpressionTests, getTypeTest) {
  EXPECT_EQ(minExpr(Integer(0), Integer(0))->getType(), MathObjectType(MathObjectType::MinMaxExpression, "MinMaxExpression"));
}
