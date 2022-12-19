#include <gtest/gtest.h>

#include "fintamath/expressions/MulExpression.hpp"

#include <fstream>

using namespace fintamath;

// TODO add tests for all public functions

TEST(MulExpressionTests, toStringTest) {
}

TEST(MulExpressionTests, getClassNameTest) {
  EXPECT_EQ(MulExpression().getClassName(), "MulExpression");
}
