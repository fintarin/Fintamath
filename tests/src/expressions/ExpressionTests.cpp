#include <gtest/gtest.h>

#include <fintamath/numbers/Rational.hpp>
#include <fstream>

#include "fintamath/expressions/Expression.hpp"

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
  EXPECT_EQ(Expression("e^101").simplify()->to<Rational>().toString(10),
            "73070599793680672726476826340615135890078390.0839607076");
  EXPECT_EQ(Expression("e^101-e^101").simplify()->toString(),
            "0");
  EXPECT_EQ(Expression("0.001-0.002").simplify()->to<Rational>().toString(10),
            "-0.001");
  EXPECT_EQ(Expression("e^(-101)").simplify()->to<Rational>().toString(10),
            "0");
  EXPECT_EQ(Expression("e^(-101)/e^(-101)").simplify()->toString(), "1");
  EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").simplify()->toString(), "1");
  EXPECT_EQ(Expression("-1!").simplify()->toString(), "-1");
  EXPECT_EQ(Expression("-100!").simplify()->toString(), "-93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");
  EXPECT_EQ(Expression("ln(3)").simplify()->to<Rational>().toString(36), "1.098612288668109691395245236922525582");
  EXPECT_EQ(Expression("ln(2)").simplify()->to<Rational>().toString(36), "0.693147180559945309417232121458176479");
  EXPECT_EQ(Expression("e").simplify()->to<Rational>().toString(36), "2.718281828459045235360287471352662498");
  EXPECT_EQ(Expression("ln(e)").simplify()->to<Rational>().toString(10), "1");
  EXPECT_EQ(Expression("sin(1)^2").simplify()->to<Rational>().toString(36), "0.708073418273571193498784114750381096");
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").simplify()->to<Rational>().toString(10), "1");
  EXPECT_EQ(Expression("sin(pi/3)").simplify()->to<Rational>().toString(36), "0.866025403784438646763723170752936183");
  EXPECT_EQ(Expression("cos(pi/3)").simplify()->to<Rational>().toString(36), "0.5");
}

TEST(ExpressionTests, testTest) {
  auto expr = Expression("e^(-101)/e^(-101)");
  auto c = expr.toString();
  auto d = expr.simplify();
}