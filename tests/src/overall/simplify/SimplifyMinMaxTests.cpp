#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyMinMaxTests, simplifyTest) {
  EXPECT_EQ(Expression("min(1)").toString(), "1");
  EXPECT_EQ(Expression("min(1,2)").toString(), "1");
  EXPECT_EQ(Expression("min(1,2,3)").toString(), "1");
  EXPECT_EQ(Expression("min(1, 2, 3, 4)").toString(), "1");
  EXPECT_EQ(Expression("min(-1, -2, -3, -4)").toString(), "-4");
  EXPECT_EQ(Expression("min(x)").toString(), "x");
  EXPECT_EQ(Expression("min(1,x)").toString(), "min(x, 1)");
  EXPECT_EQ(Expression("min(1,2,x)").toString(), "min(x, 1)");
  EXPECT_EQ(Expression("min(1, 2, x, 4)").toString(), "min(x, 1)");
  EXPECT_EQ(Expression("min(-1, x, y, -4)").toString(), "min(x, y, -4)");
  EXPECT_EQ(Expression("min(E, x, y, z)").toString(), "min(x, y, z, E)");

  EXPECT_EQ(Expression("max(1)").toString(), "1");
  EXPECT_EQ(Expression("max(1,2)").toString(), "2");
  EXPECT_EQ(Expression("max(1,2,3)").toString(), "3");
  EXPECT_EQ(Expression("max(1, 2, 3, 4)").toString(), "4");
  EXPECT_EQ(Expression("max(-1, -2, -3, -4)").toString(), "-1");
  EXPECT_EQ(Expression("max(x)").toString(), "x");
  EXPECT_EQ(Expression("max(1,x)").toString(), "max(x, 1)");
  EXPECT_EQ(Expression("max(1,2,x)").toString(), "max(x, 2)");
  EXPECT_EQ(Expression("max(1, 2, x, 4)").toString(), "max(x, 4)");
  EXPECT_EQ(Expression("max(-1, x, y, -4)").toString(), "max(x, y, -1)");
  EXPECT_EQ(Expression("max(E, x, y, z)").toString(), "max(x, y, z, E)");
}
