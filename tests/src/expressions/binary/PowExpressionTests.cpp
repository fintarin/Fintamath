#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/powers/Pow.hpp"

using namespace fintamath;

TEST(PowExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Pow(), Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::PowExpression));
}
