#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(SignExpressionTests, getTypeTest) {
  EXPECT_EQ(signExpr(Integer(0).clone())->getType(), MathObjectType::SignExpression);
}
