#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/powers/Pow.hpp"

using namespace fintamath;

TEST(PowExprTests, getTypeTest) {
  EXPECT_EQ(powExpr(Integer(0), Integer(0))->getType(), MathObjectType(MathObjectType::PowExpr, "PowExpr"));
}
