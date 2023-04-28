#include <gtest/gtest.h>

#include "fintamath/expressions/ILogicNegatableExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(ILogicNegatableExpressionTests, invertTest) {
  auto expr = cast<ILogicNegatableExpression>(
      makeFunctionExpression(And(), {Variable("a").clone(),Variable("b").clone()})->clone());

  EXPECT_EQ(expr->toString(), "a & b");
  EXPECT_EQ(expr->logicNegate()->toString(), "~a | ~b");
}
