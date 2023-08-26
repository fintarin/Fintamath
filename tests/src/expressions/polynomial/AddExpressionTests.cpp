#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(AddExpressionTests, getTypeIdTest) {
  EXPECT_EQ(addExpr(Integer(0), Integer(0))->getTypeId(), MathObjectTypeId(MathObjectType::AddExpression));
}
