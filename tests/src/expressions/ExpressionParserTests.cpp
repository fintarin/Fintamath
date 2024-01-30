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
}

TEST(ExpressionParserTests, parseFintamathNegativeTest) {
  EXPECT_THROW(parseFintamath(""), InvalidInputException);
  EXPECT_THROW(parseFintamath("1+"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1-"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1*"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1/"), InvalidInputException);
  EXPECT_THROW(parseFintamath("*1"), InvalidInputException);
  EXPECT_THROW(parseFintamath("/1"), InvalidInputException);
  EXPECT_THROW(parseFintamath(" +   "), InvalidInputException);
  EXPECT_THROW(parseFintamath("(1+2))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("5-*3"), InvalidInputException);
  EXPECT_THROW(parseFintamath("5 3 +"), InvalidInputException);
  EXPECT_THROW(parseFintamath("2.2.2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("--"), InvalidInputException);
  EXPECT_THROW(parseFintamath("."), InvalidInputException);
  EXPECT_THROW(parseFintamath(","), InvalidInputException);
  EXPECT_THROW(parseFintamath("/"), InvalidInputException);
  EXPECT_THROW(parseFintamath(";"), InvalidInputException);
  EXPECT_THROW(parseFintamath("\'"), InvalidInputException);
  EXPECT_THROW(parseFintamath("["), InvalidInputException);
  EXPECT_THROW(parseFintamath("]"), InvalidInputException);
  EXPECT_THROW(parseFintamath("!"), InvalidInputException);
  EXPECT_THROW(parseFintamath("@"), InvalidInputException);
  EXPECT_THROW(parseFintamath("\""), InvalidInputException);
  EXPECT_THROW(parseFintamath("#"), InvalidInputException);
  EXPECT_THROW(parseFintamath("№"), InvalidInputException);
  EXPECT_THROW(parseFintamath("%"), InvalidInputException);
  EXPECT_THROW(parseFintamath(":"), InvalidInputException);
  EXPECT_THROW(parseFintamath("?"), InvalidInputException);
  EXPECT_THROW(parseFintamath("*"), InvalidInputException);
  EXPECT_THROW(parseFintamath("("), InvalidInputException);
  EXPECT_THROW(parseFintamath(")"), InvalidInputException);
  EXPECT_THROW(parseFintamath("-"), InvalidInputException);
  EXPECT_THROW(parseFintamath("+"), InvalidInputException);
  EXPECT_THROW(parseFintamath("$"), InvalidInputException);
  EXPECT_THROW(parseFintamath("^"), InvalidInputException);
  EXPECT_THROW(parseFintamath("&"), InvalidInputException);
  EXPECT_THROW(parseFintamath("_"), InvalidInputException);
  EXPECT_THROW(parseFintamath("[1+1]"), InvalidInputException);
  EXPECT_THROW(parseFintamath("{1}"), InvalidInputException);
  EXPECT_THROW(parseFintamath(",2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("2,"), InvalidInputException);

  EXPECT_THROW(parseFintamath("(1"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(((2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(((2))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((2)))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(2)))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((((2)((2))))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(()())"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((()()))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((((()))))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(,) + (,)"), InvalidInputException);

  EXPECT_THROW(parseFintamath("!2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("!!2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("!2!!"), InvalidInputException);
  EXPECT_THROW(parseFintamath("!(2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("!(2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("2)!"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(2))!"), InvalidInputException);
  EXPECT_THROW(parseFintamath("!!!!!!"), InvalidInputException);

  EXPECT_THROW(parseFintamath("esin()"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(a+b)*()"), InvalidInputException);

  EXPECT_THROW(parseFintamath("sin(2,3)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(2,3) + 2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("cos(sin(2,3))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(,)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(,2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(2,)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin()"), InvalidInputException);
  EXPECT_THROW(parseFintamath("log(1)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("log()"), InvalidInputException);

  EXPECT_THROW(parseFintamath("(1 = 1) / 2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("2 + (1 = 2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(1 = 1)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(sin(1 = 1))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("sin(sin(sin(1 = 1)))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("True/True"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((1 == 1)) + ((1 == 2))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((1 == 1)) - ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("((1 == 1)) / ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(5+5)=(2=5)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1+(sin(x)<2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1/(sin(x)<2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1+False"), InvalidInputException);
  EXPECT_THROW(parseFintamath("False+1"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1=False"), InvalidInputException);
  EXPECT_THROW(parseFintamath("False=1"), InvalidInputException);
  EXPECT_THROW(parseFintamath("1&2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("x+1&x+2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("x+1&x"), InvalidInputException);
  EXPECT_THROW(parseFintamath("x&x+2"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(x&y)=(y&z)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("derivative(x=y, x)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("derivative(x&y,x)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("derivative(True,a)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(a+1)_(a>2)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(x+1)_1"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(x*2)_1"), InvalidInputException);
  EXPECT_THROW(parseFintamath("(x*2)_((x+2)_x)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("x^x_1"), InvalidInputException);
  EXPECT_THROW(parseFintamath("E&a"), InvalidInputException);
  EXPECT_THROW(parseFintamath("~Inf"), InvalidInputException);
  EXPECT_THROW(parseFintamath("~Undefined"), InvalidInputException);
  EXPECT_THROW(parseFintamath("a | Undefined"), InvalidInputException);

  EXPECT_THROW(parseFintamath("min()"), InvalidInputException);
  EXPECT_THROW(parseFintamath("min(True, False)"), InvalidInputException);
  EXPECT_THROW(parseFintamath("max()"), InvalidInputException);
  EXPECT_THROW(parseFintamath("max(True, False)"), InvalidInputException);
}
