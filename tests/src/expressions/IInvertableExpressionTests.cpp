#include <gtest/gtest.h>

#include "fintamath/expressions/IInvertableExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"

using namespace fintamath;

TEST(IInvertableExpressionTests, invertTest) {
  auto expr = cast<IInvertableExpression>(
      makeFunctionExpression(Div(), {Variable("a").clone(), Variable("b").clone()})->clone());

  EXPECT_EQ(expr->toString(), "a/b");
  EXPECT_EQ(expr->invert()->toString(), "b/a");
}
