#include <gtest/gtest.h>

#include "fintamath/expressions/AddExpression.hpp"

#include <fstream>

using namespace fintamath;

// TODO add tests for all public functions

TEST(AddExpressionTests, toStringTest) {
}

TEST(AddExpressionTests, getClassNameTest) {
  EXPECT_EQ(AddExpression().getClassName(), "AddExpression");
}
