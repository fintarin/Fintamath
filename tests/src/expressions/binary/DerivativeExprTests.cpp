#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"

using namespace fintamath;

TEST(DerivativeExprTests, getTypeTest) {
  EXPECT_EQ(derivativeExpr(Integer(0), Variable("x"))->getType(), MathObjectType(MathObjectType::DerivativeExpr, "DerivativeExpr"));
}
