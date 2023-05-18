#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/Not.hpp"

using namespace fintamath;

TEST(NotExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Not(), Integer(0).clone())->getTypeId(), MathObjectTypeId(MathObjectType::NotExpression));
}
