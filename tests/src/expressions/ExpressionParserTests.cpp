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
  EXPECT_THROW(parseExpr(""), InvalidInputException);
  EXPECT_THROW(parseExpr("1+"), InvalidInputException);
  EXPECT_THROW(parseExpr("1-"), InvalidInputException);
  EXPECT_THROW(parseExpr("1*"), InvalidInputException);
  EXPECT_THROW(parseExpr("1/"), InvalidInputException);
  EXPECT_THROW(parseExpr("*1"), InvalidInputException);
  EXPECT_THROW(parseExpr("/1"), InvalidInputException);
  EXPECT_THROW(parseExpr(" +   "), InvalidInputException);
  EXPECT_THROW(parseExpr("(1+2))"), InvalidInputException);
  EXPECT_THROW(parseExpr("5-*3"), InvalidInputException);
  EXPECT_THROW(parseExpr("5 3 +"), InvalidInputException);
  EXPECT_THROW(parseExpr("2.2.2"), InvalidInputException);
  EXPECT_THROW(parseExpr("--"), InvalidInputException);
  EXPECT_THROW(parseExpr("."), InvalidInputException);
  EXPECT_THROW(parseExpr(","), InvalidInputException);
  EXPECT_THROW(parseExpr("/"), InvalidInputException);
  EXPECT_THROW(parseExpr(";"), InvalidInputException);
  EXPECT_THROW(parseExpr("\'"), InvalidInputException);
  EXPECT_THROW(parseExpr("["), InvalidInputException);
  EXPECT_THROW(parseExpr("]"), InvalidInputException);
  EXPECT_THROW(parseExpr("!"), InvalidInputException);
  EXPECT_THROW(parseExpr("@"), InvalidInputException);
  EXPECT_THROW(parseExpr("\""), InvalidInputException);
  EXPECT_THROW(parseExpr("#"), InvalidInputException);
  EXPECT_THROW(parseExpr("№"), InvalidInputException);
  EXPECT_THROW(parseExpr("%"), InvalidInputException);
  EXPECT_THROW(parseExpr(":"), InvalidInputException);
  EXPECT_THROW(parseExpr("?"), InvalidInputException);
  EXPECT_THROW(parseExpr("*"), InvalidInputException);
  EXPECT_THROW(parseExpr("("), InvalidInputException);
  EXPECT_THROW(parseExpr(")"), InvalidInputException);
  EXPECT_THROW(parseExpr("-"), InvalidInputException);
  EXPECT_THROW(parseExpr("+"), InvalidInputException);
  EXPECT_THROW(parseExpr("$"), InvalidInputException);
  EXPECT_THROW(parseExpr("^"), InvalidInputException);
  EXPECT_THROW(parseExpr("&"), InvalidInputException);
  EXPECT_THROW(parseExpr("_"), InvalidInputException);
  EXPECT_THROW(parseExpr("[1+1]"), InvalidInputException);
  EXPECT_THROW(parseExpr("{1}"), InvalidInputException);
  EXPECT_THROW(parseExpr(",2"), InvalidInputException);
  EXPECT_THROW(parseExpr("2,"), InvalidInputException);

  EXPECT_THROW(parseExpr("(1"), InvalidInputException);
  EXPECT_THROW(parseExpr("(((2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("(((2))"), InvalidInputException);
  EXPECT_THROW(parseExpr("((2)))"), InvalidInputException);
  EXPECT_THROW(parseExpr("(2)))"), InvalidInputException);
  EXPECT_THROW(parseExpr("(2"), InvalidInputException);
  EXPECT_THROW(parseExpr("((2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("((2"), InvalidInputException);
  EXPECT_THROW(parseExpr("((((2)((2))))"), InvalidInputException);
  EXPECT_THROW(parseExpr("(()())"), InvalidInputException);
  EXPECT_THROW(parseExpr("((()()))"), InvalidInputException);
  EXPECT_THROW(parseExpr("((((()))))"), InvalidInputException);
  EXPECT_THROW(parseExpr("(,) + (,)"), InvalidInputException);

  EXPECT_THROW(parseExpr("!2"), InvalidInputException);
  EXPECT_THROW(parseExpr("!!2"), InvalidInputException);
  EXPECT_THROW(parseExpr("!2!!"), InvalidInputException);
  EXPECT_THROW(parseExpr("!(2"), InvalidInputException);
  EXPECT_THROW(parseExpr("!(2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("2)!"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(2))!"), InvalidInputException);
  EXPECT_THROW(parseExpr("!!!!!!"), InvalidInputException);

  EXPECT_THROW(parseExpr("esin()"), InvalidInputException);
  EXPECT_THROW(parseExpr("(a+b)*()"), InvalidInputException);

  EXPECT_THROW(parseExpr("sin(2,3)"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(2,3) + 2"), InvalidInputException);
  EXPECT_THROW(parseExpr("cos(sin(2,3))"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(,)"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(,2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(2,)"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin()"), InvalidInputException);
  EXPECT_THROW(parseExpr("log(1)"), InvalidInputException);
  EXPECT_THROW(parseExpr("log()"), InvalidInputException);

  EXPECT_THROW(parseExpr("(1 = 1) / 2"), InvalidInputException);
  EXPECT_THROW(parseExpr("2 + (1 = 2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(1 = 1)"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(sin(1 = 1))"), InvalidInputException);
  EXPECT_THROW(parseExpr("sin(sin(sin(1 = 1)))"), InvalidInputException);
  EXPECT_THROW(parseExpr("True/True"), InvalidInputException);
  EXPECT_THROW(parseExpr("((1 == 1)) + ((1 == 2))"), InvalidInputException);
  EXPECT_THROW(parseExpr("((1 == 1)) - ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(parseExpr("((1 == 1)) / ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(parseExpr("(5+5)=(2=5)"), InvalidInputException);
  EXPECT_THROW(parseExpr("1+(sin(x)<2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("1/(sin(x)<2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("1+False"), InvalidInputException);
  EXPECT_THROW(parseExpr("False+1"), InvalidInputException);
  EXPECT_THROW(parseExpr("1=False"), InvalidInputException);
  EXPECT_THROW(parseExpr("False=1"), InvalidInputException);
  EXPECT_THROW(parseExpr("1&2"), InvalidInputException);
  EXPECT_THROW(parseExpr("x+1&x+2"), InvalidInputException);
  EXPECT_THROW(parseExpr("x+1&x"), InvalidInputException);
  EXPECT_THROW(parseExpr("x&x+2"), InvalidInputException);
  EXPECT_THROW(parseExpr("(x&y)=(y&z)"), InvalidInputException);
  EXPECT_THROW(parseExpr("derivative(x=y, x)"), InvalidInputException);
  EXPECT_THROW(parseExpr("derivative(x&y,x)"), InvalidInputException);
  EXPECT_THROW(parseExpr("derivative(True,a)"), InvalidInputException);
  EXPECT_THROW(parseExpr("(a+1)_(a>2)"), InvalidInputException);
  EXPECT_THROW(parseExpr("(x+1)_1"), InvalidInputException);
  EXPECT_THROW(parseExpr("(x*2)_1"), InvalidInputException);
  EXPECT_THROW(parseExpr("(x*2)_((x+2)_x)"), InvalidInputException);
  EXPECT_THROW(parseExpr("x^x_1"), InvalidInputException);
  EXPECT_THROW(parseExpr("E&a"), InvalidInputException);
  EXPECT_THROW(parseExpr("~Inf"), InvalidInputException);
  EXPECT_THROW(parseExpr("~Undefined"), InvalidInputException);
  EXPECT_THROW(parseExpr("a | Undefined"), InvalidInputException);

  EXPECT_THROW(parseExpr("min()"), InvalidInputException);
  EXPECT_THROW(parseExpr("min(True, False)"), InvalidInputException);
  EXPECT_THROW(parseExpr("max()"), InvalidInputException);
  EXPECT_THROW(parseExpr("max(True, False)"), InvalidInputException);
}
