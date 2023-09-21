#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(AddExpressionTests, getTypeTest) {
  EXPECT_EQ(addExpr(Integer(0), Integer(0))->getType(), MathObjectType::AddExpression);
}
