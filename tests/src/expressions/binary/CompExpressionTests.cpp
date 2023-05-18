#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"

using namespace fintamath;

TEST(CompExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Eqv(), Integer(0).clone(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::CompExpression));
}
