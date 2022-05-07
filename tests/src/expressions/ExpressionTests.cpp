#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionTests, toStringTest) {
}

TEST(ExpressionTests, constructorTest) {
  EXPECT_EQ(Expression().toString(), "");
}

TEST(ExpressionTests, moveTest) {
  auto a = Expression("1+2-3");
  EXPECT_EQ(a.toString(), "0");
  auto b = std::move(a);
  EXPECT_TRUE(b.toString() == "0" && a.toString() == "");
  a = std::move(b);
  EXPECT_TRUE(a.toString() == "0" && b.toString() == "");
}

TEST(ExpressionTests, copyTest) {
  auto a = Expression("1+2");
  auto b = a;
  EXPECT_TRUE(a == b && &a != &b);
}

TEST(ExpressionTests, constructorSimplifyTest) {
  EXPECT_EQ(Expression("2").toString(), "2");
  EXPECT_EQ(Expression("2 + 2").toString(), "4");
  EXPECT_EQ(Expression("2 * 2").toString(), "4");
  EXPECT_EQ(Expression("2 ^ 2").toString(), "4");
  EXPECT_EQ(Expression("2 + 2 * 2").toString(), "6");
  EXPECT_EQ(Expression("(2 + 2) * 2").toString(), "8");
  EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(), "4");
  EXPECT_EQ(Expression("((((2))))").toString(), "2");
  EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(), "12");
  EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(), "16");
  EXPECT_EQ(Expression("2^2^2^2").toString(), "65536");
  EXPECT_EQ(Expression("(2-2)").toString(), "0");
  EXPECT_EQ(Expression("0^1").toString(), "0");
  EXPECT_EQ(Expression("2^0").toString(), "1");
  EXPECT_EQ(Expression("0/3").toString(), "0");
  EXPECT_EQ(Expression("1/3").toString(), "1/3");
  EXPECT_EQ(Expression("-2+3").toString(), "1");

  EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(), "a");
  EXPECT_EQ(Expression("a+a").toString(), "2*a");
  EXPECT_EQ(Expression("a-a").toString(), "0");
  EXPECT_EQ(Expression("(a+b)-b").toString(), "a");

  EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(), "b*b+a*a+3*a*b");
}

TEST(ExpressionsTest, simplifyTest) {
  EXPECT_EQ(Expression("e^101").simplify()->toString(),
            "73070599793680672726476826340615135890078390.083960707616445859670987727649317305");
  EXPECT_EQ(Expression("e^101-e^101").simplify()->toString(), "0");
  EXPECT_EQ(Expression("0.001-0.002").simplify()->toString(), "-1/1000");
  EXPECT_EQ(Expression("e^(-101)").simplify()->toString(), "0");
  EXPECT_EQ(Expression("e^(-101)/e^(-101)").simplify()->toString(), "1");
  EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").simplify()->toString(), "1");
  EXPECT_EQ(Expression("-1!").simplify()->toString(), "-1");
  EXPECT_EQ(Expression("-100!").simplify()->toString(),
            "-933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536"
            "97920827223758251185210916864000000000000000000000000");
  EXPECT_EQ(Expression("ln(3)").simplify()->toString(), "1.098612288668109691395245236922525705");
  EXPECT_EQ(Expression("ln(2)").simplify()->toString(), "0.693147180559945309417232121458176568");
  EXPECT_EQ(Expression("e").simplify()->toString(), "2.718281828459045235360287471352662498");
  EXPECT_EQ(Expression("ln(e)").simplify()->toString(), "1");
  EXPECT_EQ(Expression("sin(1)^2").simplify()->toString(), "0.708073418273571193498784114750381095");
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").simplify()->toString(), "1");
  EXPECT_EQ(Expression("sin(pi/3)").simplify()->toString(), "0.866025403784438646763723170752936183");
  EXPECT_EQ(Expression("cos(pi/3)").simplify()->toString(), "0.5");
}

TEST(ExpressionTests, testTest) {
  auto expr = Expression("e^(-101)/e^(-101)");
  auto c = expr.toString();
  auto d = expr.simplify();
}