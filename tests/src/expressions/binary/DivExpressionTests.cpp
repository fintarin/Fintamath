#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"

using namespace fintamath;

TEST(DivExpressionTests, getTypeTest) {
  EXPECT_EQ(divExpr(Integer(0), Integer(0))->getType(), MathObjectType::DivExpression);
}
