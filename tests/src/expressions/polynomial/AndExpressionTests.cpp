#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(AndExpressionTests, getTypeTest) {
  EXPECT_EQ(andExpr(Integer(0), Integer(0))->getType(), MathObjectType::AndExpression);
}
