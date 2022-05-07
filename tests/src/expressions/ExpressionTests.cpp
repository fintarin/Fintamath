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
  EXPECT_EQ(Expression("--5").toString(), "5");
  EXPECT_EQ(Expression("5*-3").toString(), "-15");
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

TEST(ExpressionTest, negativeTests) {
  EXPECT_ANY_THROW(Expression(""));
  EXPECT_ANY_THROW(Expression("1+"));
  EXPECT_ANY_THROW(Expression("1-"));
  EXPECT_ANY_THROW(Expression("1*"));
  EXPECT_ANY_THROW(Expression("1/"));
  EXPECT_ANY_THROW(Expression(" +   "));
  EXPECT_ANY_THROW(Expression("(1+2))"));
  EXPECT_ANY_THROW(Expression("5-*3"));
  EXPECT_ANY_THROW(Expression("((()()))"));
  EXPECT_ANY_THROW(Expression("2.a"));
  EXPECT_ANY_THROW(Expression("2.2.2"));
  EXPECT_ANY_THROW(Expression("sin"));
  EXPECT_ANY_THROW(Expression("cos"));
  EXPECT_ANY_THROW(Expression("log"));
  EXPECT_ANY_THROW(Expression("ln"));
  EXPECT_ANY_THROW(Expression("--"));
  EXPECT_ANY_THROW(Expression("."));
  EXPECT_ANY_THROW(Expression(","));
  EXPECT_ANY_THROW(Expression("/"));
  EXPECT_ANY_THROW(Expression(";"));
  EXPECT_ANY_THROW(Expression("\'"));
  EXPECT_ANY_THROW(Expression("["));
  EXPECT_ANY_THROW(Expression("]"));
  EXPECT_ANY_THROW(Expression("!"));
  EXPECT_ANY_THROW(Expression("@"));
  EXPECT_ANY_THROW(Expression("\""));
  EXPECT_ANY_THROW(Expression("#"));
  EXPECT_ANY_THROW(Expression("№"));
  EXPECT_ANY_THROW(Expression("%"));
  EXPECT_ANY_THROW(Expression(":"));
  EXPECT_ANY_THROW(Expression("?"));
  EXPECT_ANY_THROW(Expression("*"));
  EXPECT_ANY_THROW(Expression("("));
  EXPECT_ANY_THROW(Expression(")"));
  EXPECT_ANY_THROW(Expression("-"));
  EXPECT_ANY_THROW(Expression("+"));
  EXPECT_ANY_THROW(Expression("$"));
  EXPECT_ANY_THROW(Expression("^"));
  EXPECT_ANY_THROW(Expression("&"));
  EXPECT_ANY_THROW(Expression("_"));
  EXPECT_ANY_THROW(Expression("[1+1]"));
  EXPECT_ANY_THROW(Expression("{1}"));
  EXPECT_ANY_THROW(Expression("(1"));
  EXPECT_ANY_THROW(Expression("(((2)"));
  EXPECT_ANY_THROW(Expression("(((2))"));
  EXPECT_ANY_THROW(Expression("((2)))"));
  EXPECT_ANY_THROW(Expression("(2)))"));
  EXPECT_ANY_THROW(Expression("(2"));
  EXPECT_ANY_THROW(Expression("((2)"));
  EXPECT_ANY_THROW(Expression("((2"));
  EXPECT_ANY_THROW(Expression("(()())"));
  EXPECT_ANY_THROW(Expression("((((()))))"));
  EXPECT_ANY_THROW(Expression("((((2)((2))))"));
  EXPECT_ANY_THROW(Expression("!2"));
  EXPECT_ANY_THROW(Expression("!!2"));
  EXPECT_ANY_THROW(Expression("!2!!"));
  EXPECT_ANY_THROW(Expression("!(2"));
  EXPECT_ANY_THROW(Expression("!(2)"));
  EXPECT_ANY_THROW(Expression("2)!"));
  EXPECT_ANY_THROW(Expression("1/0"));
  EXPECT_ANY_THROW(Expression("0^0"));
  EXPECT_ANY_THROW(Expression("sin(2))!"));

  EXPECT_ANY_THROW(Expression("(-1)!").simplify());
  EXPECT_ANY_THROW(Expression("(2/3)!").simplify());
  EXPECT_ANY_THROW(Expression("(-1)!!").simplify());
  EXPECT_ANY_THROW(Expression("(2/3)!!").simplify());
  EXPECT_ANY_THROW(Expression("e!").simplify());
  EXPECT_ANY_THROW(Expression("sqrt(-1)").simplify());
  EXPECT_ANY_THROW(Expression("ln(0)").simplify());
  EXPECT_ANY_THROW(Expression("ln(-1)").simplify());
  EXPECT_ANY_THROW(Expression("log(-1, 1)").simplify());
  EXPECT_ANY_THROW(Expression("log(0, 1)").simplify());
  EXPECT_ANY_THROW(Expression("log(1, 0)").simplify());
  EXPECT_ANY_THROW(Expression("lb(-1)").simplify());
  EXPECT_ANY_THROW(Expression("lg(-1)").simplify());
  EXPECT_ANY_THROW(Expression("(-1)^(2/3)").simplify());
  EXPECT_ANY_THROW(Expression("tan(pi/2)").simplify());
  EXPECT_ANY_THROW(Expression("cot(0)").simplify());
  EXPECT_ANY_THROW(Expression("asin(2)").simplify());
  EXPECT_ANY_THROW(Expression("acos(2)").simplify());
  EXPECT_ANY_THROW(Expression("tan(3/2*pi)").simplify());
  EXPECT_ANY_THROW(Expression("cot(2*pi)").simplify());

  EXPECT_ANY_THROW(
      Expression("1-2*sin((pi/6))*sqrt((1/2)*(1-1-2*sin((pi/6))*sqrt((1/2)*(1-cos(2(pi/6))))))").simplify());
}
