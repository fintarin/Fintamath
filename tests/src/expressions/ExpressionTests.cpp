#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(ExpressionTests, stringConstructorTest) {
  EXPECT_EQ(Expression("2 + 2").toString(), "(add 2 2)");
  EXPECT_EQ(Expression("2 + 2 + 2 + 2").toString(), "(add 2 2 2 2)");
  EXPECT_EQ(Expression("2 + 2 * 2 + 2").toString(), "(add 2 (mul 2 2) 2)");
  EXPECT_EQ(Expression("add(2, 2, 2, 2)").toString(), "(add 2 2 2 2)");
  EXPECT_EQ(Expression("mul(2, 2, 2, 2)").toString(), "(mul 2 2 2 2)");
}
