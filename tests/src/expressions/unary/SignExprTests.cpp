#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Sign.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(SignExprTests, getTypeTest) {
  EXPECT_EQ(signExpr(Integer(0).clone())->getType(), MathObjectType(MathObjectType::SignExpr, "SignExpr"));
}
