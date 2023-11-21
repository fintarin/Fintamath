#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(AbsExpressionTests, getTypeTest) {
  EXPECT_EQ(absExpr(Integer(0).clone())->getType(), MathObjectType::AbsExpression);
}
