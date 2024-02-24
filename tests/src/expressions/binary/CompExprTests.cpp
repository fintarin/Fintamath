#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"

using namespace fintamath;

TEST(CompExprTests, getTypeTest) {
  EXPECT_EQ(eqvExpr(Integer(0), Integer(0))->getType(), MathObjectType(MathObjectType::CompExpr, "CompExpr"));
}
