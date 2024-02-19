#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionParser.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionParserTests, parseExprTest) {
  EXPECT_EQ(parseExpr("36/(8-6)3")->toString(), "36/(8 - 6) 3");
  EXPECT_EQ(parseExpr("2%")->toString(), "2/100");
  EXPECT_EQ(parseExpr("2.35%")->toString(), "(47/20)/100");
  EXPECT_EQ(parseExpr("1100*4.76%")->toString(), "1100 (119/25)/100");
  EXPECT_EQ(parseExpr("2.35%%%%")->toString(), "((((47/20)/100)/100)/100)/100");
  EXPECT_EQ(parseExpr("1100*4.76%1100*4.76%")->toString(), "1100 (119/25)/100*1100 (119/25)/100");
  EXPECT_EQ(parseExpr("((((((5)/(8)))/(1)))/(((((((9)/(4)))/(0)))/(5))))")->toString(), "((5/8)/1)/(((9/4)/0)/5)");
  EXPECT_EQ(parseExpr("2%a")->toString(), "2/100 a");
  EXPECT_EQ(parseExpr("2!!!!a!!!")->toString(), "2!!!! a!!!");
  EXPECT_EQ(parseExpr("sin a")->toString(), "sin(a)");
  EXPECT_EQ(parseExpr("s i n a")->toString(), "s i n a");
  EXPECT_EQ(parseExpr("a(2)")->toString(), "a 2");
  EXPECT_EQ(parseExpr("(2)a")->toString(), "2 a");
  EXPECT_EQ(parseExpr("Ea")->toString(), "E a");
  EXPECT_EQ(parseExpr("aE")->toString(), "a E");
  EXPECT_EQ(parseExpr("aEE")->toString(), "a E E");
  EXPECT_EQ(parseExpr("EEa")->toString(), "E E a");
  EXPECT_EQ(parseExpr("x123")->toString(), "x 123");
  EXPECT_EQ(parseExpr("x^y!")->toString(), "(x^y)!");
  EXPECT_EQ(parseExpr("lnE")->toString(), "ln(E)");
  EXPECT_EQ(parseExpr("lncossinE")->toString(), "ln(cos(sin(E)))");
  EXPECT_EQ(parseExpr("ln cos sin a")->toString(), "ln(cos(sin(a)))");
  EXPECT_EQ(parseExpr("log((Pi),(E)^((Pi)))")->toString(), "log(Pi, E^Pi)");
  EXPECT_EQ(parseExpr("lb100")->toString(), "log(2, 100)");
  EXPECT_EQ(parseExpr("log(4/9, 2/3)")->toString(), "log(4/9, 2/3)");
  EXPECT_EQ(parseExpr("60deg")->toString(), "60 Pi/180");
  EXPECT_EQ(parseExpr("adeg")->toString(), "a Pi/180");
}

TEST(ExpressionParserTests, parseExprNegativeTest) {
  EXPECT_THAT(
      [] { parseExpr(""); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1+"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1-"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1*"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1/"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("*1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("/1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr(" +   "); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(1+2))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("5-*3"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("5 3 +"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("2.2.2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("--"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("."); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr(","); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("/"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr(";"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("\'"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("["); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("]"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("@"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("\""); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("#"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("№"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("%"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr(":"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("?"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("*"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("("); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr(")"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("-"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("+"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("$"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("^"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("&"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("_"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("[1+1]"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("{1}"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr(",2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("2,"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));

  EXPECT_THAT(
      [] { parseExpr("(1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(((2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(((2))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((2)))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(2)))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((((2)((2))))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(()())"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((()()))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((((()))))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(,) + (,)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));

  EXPECT_THAT(
      [] { parseExpr("!2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("!!2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("!2!!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("!(2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("!(2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("2)!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(2))!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("!!!!!!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));

  EXPECT_THAT(
      [] { parseExpr("esin()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(a+b)*()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));

  EXPECT_THAT(
      [] { parseExpr("sin(2,3)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(2,3) + 2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("cos(sin(2,3))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(,)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(,2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(2,)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("log(1)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("log()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));

  EXPECT_THAT(
      [] { parseExpr("(1 = 1) / 2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("2 + (1 = 2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(1 = 1)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(sin(1 = 1))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("sin(sin(sin(1 = 1)))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("True/True"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((1 == 1)) + ((1 == 2))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((1 == 1)) - ((1 == 1))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("((1 == 1)) / ((1 == 1))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(5+5)=(2=5)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1+(sin(x)<2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1/(sin(x)<2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1+False"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("False+1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1=False"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("False=1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("1&2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("x+1&x+2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("x+1&x"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("x&x+2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(x&y)=(y&z)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("derivative(x=y, x)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("derivative(x&y,x)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("derivative(True,a)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(a+1)_(a>2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(x+1)_1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(x*2)_1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("(x*2)_((x+2)_x)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("x^x_1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("E&a"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("~Inf"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("~Undefined"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("a | Undefined"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));

  EXPECT_THAT(
      [] { parseExpr("min()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("min(True, False)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("max()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
  EXPECT_THAT(
      [] { parseExpr("max(True, False)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("")));
}
