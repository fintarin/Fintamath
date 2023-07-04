#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(AndExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(And(), Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::AndExpression));
}
