#include <gtest/gtest.h>

#include "fintamath/expressions/EqvExpression.hpp"

#include <fstream>

using namespace fintamath;

TEST(EqvExpressionTests, toStringTest) {
  // EXPECT_EQ(Expression("a+5<3").toString(), "a+5<3");
}

TEST(EqvExpressionTests, getClassNameTest) {
  EXPECT_EQ(EqvExpression().getClassName(), "EqvExpression");
}
