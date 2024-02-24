#include <gtest/gtest.h>

#include "fintamath/functions/ntheory/Floor.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(FloorCeilExprTests, getTypeTest) {
  EXPECT_EQ(floorExpr(Integer(0).clone())->getType(), MathObjectType(MathObjectType::FloorCeilExpr, "FloorCeilExpr"));
}
