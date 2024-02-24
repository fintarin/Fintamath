#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"

using namespace fintamath;

TEST(AndExprTests, getTypeTest) {
  EXPECT_EQ(andExpr(Boolean(), Boolean())->getType(), MathObjectType(MathObjectType::AndExpr, "AndExpr"));
}
