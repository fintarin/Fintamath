#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/INegatableExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

using namespace fintamath;

TEST(INegatableExpressionTests, invertTest) {
  auto expr = cast<INegatableExpression>(makeFunctionExpression(Mul(), Variable("a").clone(), TWO.clone()));

  EXPECT_EQ(expr->toString(), "2 a");
  EXPECT_EQ(expr->negate()->toString(), "-2 a");
}
