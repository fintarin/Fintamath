#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"

using namespace fintamath;

TEST(NegExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Neg(), Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::NegExpression));
}
