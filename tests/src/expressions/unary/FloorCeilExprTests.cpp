#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(FloorCeilExprTests, getClassTest) {
  const auto expr = floorExpr(Integer(0).clone());

  EXPECT_EQ(expr->getClass()->getName(), "FloorCeilExpr");
  EXPECT_EQ(expr->getClass()->getParent(), IUnaryExpression::getClassStatic());
}
