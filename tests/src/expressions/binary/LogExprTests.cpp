#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logarithms/Log.hpp"

using namespace fintamath;

TEST(LogExprTests, getTypeTest) {
  EXPECT_EQ(logExpr(Integer(0), Integer(0))->getType(), MathObjectType(MathObjectType::LogExpr, "LogExpr"));
}
