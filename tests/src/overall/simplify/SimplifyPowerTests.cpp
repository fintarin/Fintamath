#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyPowerTests, simplifyTest) {
  EXPECT_EQ(Expression("sqrt0").toString(),
            "0");
  EXPECT_EQ(Expression("sqrt(25)").toString(),
            "5");
  EXPECT_EQ(Expression("sqrt(144/25)").toString(),
            "12/5");
  EXPECT_EQ(Expression("sqrt(50)").toString(),
            "5 sqrt(2)");
  EXPECT_EQ(Expression("sqrt(26)").toString(),
            "sqrt(26)");
  EXPECT_EQ(Expression("sqrt(145/26)").toString(),
            "sqrt(3770)/26");
  EXPECT_EQ(Expression("sqrt(169/3)").toString(),
            "(13 sqrt(3))/3");
  EXPECT_EQ(Expression("sqrt(168/25)").toString(),
            "(2 sqrt(42))/5");
  EXPECT_EQ(Expression("root(4, 2)").toString(),
            "2");
  EXPECT_EQ(Expression("root(8, 3)").toString(),
            "2");
  EXPECT_EQ(Expression("root(16, 4)").toString(),
            "2");
  EXPECT_EQ(Expression("root(27, 3)").toString(),
            "3");
  EXPECT_EQ(Expression("root(0, 3)").toString(),
            "0");

  EXPECT_EQ(Expression("4^(1/2)").toString(),
            "2");
  EXPECT_EQ(Expression("8^(1/3)").toString(),
            "2");
  EXPECT_EQ(Expression("8^(4/3)").toString(),
            "16");
  EXPECT_EQ(Expression("7 2^(2/3)").toString(),
            "7 root(4, 3)");
  EXPECT_EQ(Expression("2^(2/3) 3^(2/3)").toString(),
            "root(36, 3)");
  EXPECT_EQ(Expression("2^(2/3) 7^(2/3) 3^(3/4)").toString(),
            "root(196, 3) root(27, 4)");
  EXPECT_EQ(Expression("2^(2/3) 1/7^(2/3) 3^(3/4)").toString(),
            "(root(28, 3) root(27, 4))/7");

  EXPECT_EQ(Expression("1/sqrt(3)").toString(),
            "sqrt(3)/3");
  EXPECT_EQ(Expression("1/root(3, 3)").toString(),
            "root(9, 3)/3");
  EXPECT_EQ(Expression("1/root(3, 4)").toString(),
            "root(27, 4)/3");
  EXPECT_EQ(Expression("sqrt(2) / (sqrt(2/3) sqrt(8))").toString(),
            "sqrt(6)/4");
  EXPECT_EQ(Expression("(sqrt(8) sqrt(2/3)) / sqrt(2)").toString(),
            "(2 sqrt(6))/3");

  EXPECT_EQ(Expression("(x/y)^2").toString(),
            "(x^2)/(y^2)");
  EXPECT_EQ(Expression("(x/y)^(1/2)").toString(),
            "sqrt(x/y)");
  EXPECT_EQ(Expression("(x/y)^(1/3)").toString(),
            "root(x/y, 3)");
  EXPECT_EQ(Expression("(x/y)^(-1/2)").toString(),
            "1/sqrt(x/y)");
  EXPECT_EQ(Expression("(x/y)^(-1/3)").toString(),
            "1/root(x/y, 3)");
  EXPECT_EQ(Expression("(x/y)^x").toString(),
            "(x/y)^x");
  EXPECT_EQ(Expression("(x/y)^(1/x)").toString(),
            "root(x/y, x)");

  EXPECT_EQ(Expression("sqrt(x^2)").toString(),
            "sqrt(x^2)");
  EXPECT_EQ(Expression("sqrt(x)^2").toString(),
            "x");
  EXPECT_EQ(Expression("(x^10)^(1/10)").toString(),
            "root(x^10, 10)");
  EXPECT_EQ(Expression("(x^(1/10))^10").toString(),
            "x");
  EXPECT_EQ(Expression("(x^3)^(1/3)").toString(),
            "root(x^3, 3)");
  EXPECT_EQ(Expression("(x^(1/3))^3").toString(),
            "x");
  EXPECT_EQ(Expression("root(x^(-2), -2)").toString(),
            "1/sqrt(1/(x^2))");
  EXPECT_EQ(Expression("root(0, x)").toString(),
            "0");
}
