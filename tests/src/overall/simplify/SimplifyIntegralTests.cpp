#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyIntegralTests, simplifyTest) {
  // TODO: integral
  EXPECT_EQ(Expression("integral(x, x)").toString(),
            "integral(x, x)");
  EXPECT_EQ(Expression("integral(x+x, x)").toString(),
            "integral(2 x, x)");
  EXPECT_EQ(Expression("integral(x, x) + integral(b, b)").toString(),
            "integral(b, b) + integral(x, x)");
}
