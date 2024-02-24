#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"

using namespace fintamath;

TEST(TrigExprTests, getTypeTest) {
  EXPECT_EQ(sinExpr(Integer(0).clone())->getType(), MathObjectType(MathObjectType::TrigExpr, "TrigExpr"));
}
