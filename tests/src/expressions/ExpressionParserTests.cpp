#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionParser.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionParserTests, parseFintamathTest) {
  EXPECT_EQ(parseFintamath("36/(8-6)3")->toString(), "36/(8 - 6) 3");
  EXPECT_EQ(parseFintamath("2%")->toString(), "2/100");
  EXPECT_EQ(parseFintamath("2.35%")->toString(), "(47/20)/100");
  EXPECT_EQ(parseFintamath("1100*4.76%")->toString(), "1100 (119/25)/100");
  EXPECT_EQ(parseFintamath("2.35%%%%")->toString(), "((((47/20)/100)/100)/100)/100");
  EXPECT_EQ(parseFintamath("1100*4.76%1100*4.76%")->toString(), "1100 (119/25)/100*1100 (119/25)/100");
  EXPECT_EQ(parseFintamath("((((((5)/(8)))/(1)))/(((((((9)/(4)))/(0)))/(5))))")->toString(), "((5/8)/1)/(((9/4)/0)/5)");
  EXPECT_EQ(parseFintamath("2%a")->toString(), "2/100 a");
  EXPECT_EQ(parseFintamath("2!!!!a!!!")->toString(), "2!!!! a!!!");
  EXPECT_EQ(parseFintamath("sin a")->toString(), "sin(a)");
  EXPECT_EQ(parseFintamath("s i n a")->toString(), "s i n a");
  EXPECT_EQ(parseFintamath("a(2)")->toString(), "a 2");
  EXPECT_EQ(parseFintamath("(2)a")->toString(), "2 a");
  EXPECT_EQ(parseFintamath("Ea")->toString(), "E a");
  EXPECT_EQ(parseFintamath("aE")->toString(), "a E");
  EXPECT_EQ(parseFintamath("aEE")->toString(), "a E E");
  EXPECT_EQ(parseFintamath("EEa")->toString(), "E E a");
  EXPECT_EQ(parseFintamath("x123")->toString(), "x 123");
  EXPECT_EQ(parseFintamath("x^y!")->toString(), "(x^y)!");
  EXPECT_EQ(parseFintamath("lnE")->toString(), "ln(E)");
  EXPECT_EQ(parseFintamath("lncossinE")->toString(), "ln(cos(sin(E)))");
  EXPECT_EQ(parseFintamath("ln cos sin a")->toString(), "ln(cos(sin(a)))");
  EXPECT_EQ(parseFintamath("log((Pi),(E)^((Pi)))")->toString(), "log(Pi, E^Pi)");
  EXPECT_EQ(parseFintamath("lb100")->toString(), "log(2, 100)");
  EXPECT_EQ(parseFintamath("log(4/9, 2/3)")->toString(), "log(4/9, 2/3)");
  EXPECT_EQ(parseFintamath("60deg")->toString(), "60 Pi/180");
  EXPECT_EQ(parseFintamath("adeg")->toString(), "a Pi/180");

  EXPECT_THROW(parseFintamath("(1 = 1) / 2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1+"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((((()))))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(,) + (,)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("--"), InvalidInputException);
}
