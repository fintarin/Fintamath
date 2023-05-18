#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(SumExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(Add(), Integer(0).clone(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::SumExpression));
}
