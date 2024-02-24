#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/Not.hpp"

using namespace fintamath;

TEST(NotExprTests, getTypeTest) {
  EXPECT_EQ(notExpr(Boolean())->getType(), MathObjectType(MathObjectType::NotExpr, "NotExpr"));
}
