#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"

using namespace fintamath;

TEST(MulExpressionTests, getTypeIdTest) {
  EXPECT_EQ(mulExpr(Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::MulExpression));
}
