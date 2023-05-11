#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/INegatableExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"

using namespace fintamath;

TEST(INegatableExpressionTests, invertTest) {
  auto expr = cast<INegatableExpression>(makeExprSimpl(Mul(), Variable("a").clone(), std::make_shared<Integer>(2)));

  EXPECT_EQ(expr->toString(), "2 a");
  EXPECT_EQ(expr->negate()->toString(), "-2 a");
}
