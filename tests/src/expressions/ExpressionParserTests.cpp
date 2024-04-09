#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionParserTests, parseRawExprTest) {
  EXPECT_EQ(parseRawExpr("36/(8-6)3")->toString(), "36/(8 - 6) 3");
  EXPECT_EQ(parseRawExpr("2%")->toString(), "2/100");
  EXPECT_EQ(parseRawExpr("2.35%")->toString(), "(47/20)/100");
  EXPECT_EQ(parseRawExpr("1100*4.76%")->toString(), "1100 (119/25)/100");
  EXPECT_EQ(parseRawExpr("2.35%%%%")->toString(), "((((47/20)/100)/100)/100)/100");
  EXPECT_EQ(parseRawExpr("1100*4.76%1100*4.76%")->toString(), "1100 (119/25)/100*1100 (119/25)/100");
  EXPECT_EQ(parseRawExpr("((((((5)/(8)))/(1)))/(((((((9)/(4)))/(0)))/(5))))")->toString(), "((5/8)/1)/(((9/4)/0)/5)");
  EXPECT_EQ(parseRawExpr("2%a")->toString(), "2/100 a");
  EXPECT_EQ(parseRawExpr("2!!!!a!!!")->toString(), "2!!!! a!!!");
  EXPECT_EQ(parseRawExpr("sin a")->toString(), "sin(a)");
  EXPECT_EQ(parseRawExpr("s i n a")->toString(), "s i n a");
  EXPECT_EQ(parseRawExpr("a(2)")->toString(), "a 2");
  EXPECT_EQ(parseRawExpr("(2)a")->toString(), "2 a");
  EXPECT_EQ(parseRawExpr("Ea")->toString(), "E a");
  EXPECT_EQ(parseRawExpr("aE")->toString(), "a E");
  EXPECT_EQ(parseRawExpr("aEE")->toString(), "a E E");
  EXPECT_EQ(parseRawExpr("EEa")->toString(), "E E a");
  EXPECT_EQ(parseRawExpr("x123")->toString(), "x 123");
  EXPECT_EQ(parseRawExpr("x^y!")->toString(), "(x^y)!");
  EXPECT_EQ(parseRawExpr("lnE")->toString(), "ln(E)");
  EXPECT_EQ(parseRawExpr("lncossinE")->toString(), "ln(cos(sin(E)))");
  EXPECT_EQ(parseRawExpr("ln cos sin a")->toString(), "ln(cos(sin(a)))");
  EXPECT_EQ(parseRawExpr("log((Pi),(E)^((Pi)))")->toString(), "log(Pi, E^Pi)");
  EXPECT_EQ(parseRawExpr("lb100")->toString(), "log(2, 100)");
  EXPECT_EQ(parseRawExpr("log(4/9, 2/3)")->toString(), "log(4/9, 2/3)");
  EXPECT_EQ(parseRawExpr("60deg")->toString(), "60 Pi/180");
  EXPECT_EQ(parseRawExpr("adeg")->toString(), "a Pi/180");
}

TEST(ExpressionParserTests, parseRawExprNegativeTest) {
  EXPECT_THAT(
      [] { parseRawExpr(""); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"\" (empty input)")));
  EXPECT_THAT(
      [] { parseRawExpr("1+"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1+\" (incomplite expression with operator \"+\")")));
  EXPECT_THAT(
      [] { parseRawExpr("1-"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1-\" (incomplite expression with operator \"-\")")));
  EXPECT_THAT(
      [] { parseRawExpr("1*"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1*\" (incomplite expression with operator \"*\")")));
  EXPECT_THAT(
      [] { parseRawExpr("1/"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1/\" (incomplite expression with operator \"/\")")));
  EXPECT_THAT(
      [] { parseRawExpr("*1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"*1\" (incomplite expression with operator \"*\")")));
  EXPECT_THAT(
      [] { parseRawExpr("/1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"/1\" (incomplite expression with operator \"/\")")));
  EXPECT_THAT(
      [] { parseRawExpr(" +   "); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \" +   \" (incomplite expression with operator \"+\")")));
  EXPECT_THAT(
      [] { parseRawExpr("(1+2))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(1+2))\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("5-*3"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"5-*3\" (incomplite expression with operator \"*\")")));
  EXPECT_THAT(
      [] { parseRawExpr("5 3 +"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"5 3 +\" (incomplite expression with operator \"+\")")));
  EXPECT_THAT(
      [] { parseRawExpr("2.2.2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"2.2.2\" (invalid term \"2.2.2\")")));
  EXPECT_THAT(
      [] { parseRawExpr("--"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"--\" (incomplite expression with operator \"-\")")));
  EXPECT_THAT(
      [] { parseRawExpr("."); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \".\" (invalid term \".\")")));
  EXPECT_THAT(
      [] { parseRawExpr(","); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \",\" (incomplite expression with operator \",\")")));
  EXPECT_THAT(
      [] { parseRawExpr("/"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"/\" (incomplite expression with operator \"/\")")));
  EXPECT_THAT(
      [] { parseRawExpr(";"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \";\" (invalid term \";\")")));
  EXPECT_THAT(
      [] { parseRawExpr("\'"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"'\" (invalid term \"'\")")));
  EXPECT_THAT(
      [] { parseRawExpr("["); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"[\" (invalid term \"[\")")));
  EXPECT_THAT(
      [] { parseRawExpr("]"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"]\" (invalid term \"]\")")));
  EXPECT_THAT(
      [] { parseRawExpr("!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"!\" (incomplite expression with operator \"!\")")));
  EXPECT_THAT(
      [] { parseRawExpr("@"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"@\" (invalid term \"@\")")));
  EXPECT_THAT(
      [] { parseRawExpr("\""); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"\"\" (invalid term \"\"\")")));
  EXPECT_THAT(
      [] { parseRawExpr("#"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"#\" (invalid term \"#\")")));
  EXPECT_THAT(
      [] { parseRawExpr("%"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"%\" (incomplite expression with operator \"%\")")));
  EXPECT_THAT(
      [] { parseRawExpr(":"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \":\" (invalid term \":\")")));
  EXPECT_THAT(
      [] { parseRawExpr("?"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"?\" (invalid term \"?\")")));
  EXPECT_THAT(
      [] { parseRawExpr("*"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"*\" (incomplite expression with operator \"*\")")));
  EXPECT_THAT(
      [] { parseRawExpr("("); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr(")"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \")\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("-"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"-\" (incomplite expression with operator \"-\")")));
  EXPECT_THAT(
      [] { parseRawExpr("+"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"+\" (incomplite expression with operator \"+\")")));
  EXPECT_THAT(
      [] { parseRawExpr("^"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"^\" (incomplite expression with operator \"^\")")));
  EXPECT_THAT(
      [] { parseRawExpr("&"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"&\" (incomplite expression with operator \"&\")")));
  EXPECT_THAT(
      [] { parseRawExpr("_"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"_\" (incomplite expression with operator \"_\")")));
  EXPECT_THAT(
      [] { parseRawExpr("[1+1]"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"[1+1]\" (invalid term \"[\")")));
  EXPECT_THAT(
      [] { parseRawExpr("{1}"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"{1}\" (invalid term \"{\")")));
  EXPECT_THAT(
      [] { parseRawExpr(",2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \",2\" (incomplite expression with operator \",\")")));
  EXPECT_THAT(
      [] { parseRawExpr("2,"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"2,\" (incomplite expression with operator \",\")")));
  EXPECT_THAT(
      [] { parseRawExpr("(1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(1\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("(((2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(((2)\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("(((2))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(((2))\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("((2)))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((2)))\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("(2)))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(2)))\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("(2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(2\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("((2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((2)\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("((2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((2\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("((((2)((2))))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((((2)((2))))\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("(()())"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(()())\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("((()()))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((()()))\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("((((()))))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((((()))))\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("(,) + (,)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(,) + (,)\" (incomplite expression with operator \",\")")));
  EXPECT_THAT(
      [] { parseRawExpr("!2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"!2\" (incomplite expression with operator \"!\")")));
  EXPECT_THAT(
      [] { parseRawExpr("!!2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"!!2\" (incomplite expression with operator \"!\")")));
  EXPECT_THAT(
      [] { parseRawExpr("!2!!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"!2!!\" (incomplite expression with operator \"!\")")));
  EXPECT_THAT(
      [] { parseRawExpr("!(2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"!(2\" (incomplite expression with operator \"!\")")));
  EXPECT_THAT(
      [] { parseRawExpr("!(2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"!(2)\" (incomplite expression with operator \"!\")")));
  EXPECT_THAT(
      [] { parseRawExpr("2)!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"2)!\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(2))!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(2))!\" (bracket mismatch)")));
  EXPECT_THAT(
      [] { parseRawExpr("!!!!!!"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"!!!!!!\" (incomplite expression with operator \"!\")")));
  EXPECT_THAT(
      [] { parseRawExpr("esin()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"esin()\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("(a+b)*()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(a+b)*()\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(2,3)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(2,3)\" (function \"sin\" with 2 arguments not found)")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(2,3) + 2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(2,3) + 2\" (function \"sin\" with 2 arguments not found)")));
  EXPECT_THAT(
      [] { parseRawExpr("cos(sin(2,3))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"cos(sin(2,3))\" (function \"sin\" with 2 arguments not found)")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(,)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(,)\" (incomplite expression with operator \",\")")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(,2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(,2)\" (incomplite expression with operator \",\")")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(2,)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(2,)\" (incomplite expression with operator \",\")")));
  EXPECT_THAT(
      [] { parseRawExpr("sin()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin()\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("log(1)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"log(1)\" (function \"log\" with 1 arguments not found)")));
  EXPECT_THAT(
      [] { parseRawExpr("log()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"log()\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("(1 = 1) / 2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(1 = 1) / 2\" (unable to call Div \"/\" with argument #0 Boolean \"1 = 1\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("2 + (1 = 2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"2 + (1 = 2)\" (unable to call AddOper \"+\" with argument #1 Boolean \"1 = 2\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(1 = 1)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(1 = 1)\" (unable to call Sin \"sin\" with argument #0 Boolean \"1 = 1\" (expected INumber))")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(sin(1 = 1))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(sin(1 = 1))\" (unable to call Sin \"sin\" with argument #0 Boolean \"1 = 1\" (expected INumber))")));
  EXPECT_THAT(
      [] { parseRawExpr("sin(sin(sin(1 = 1)))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"sin(sin(sin(1 = 1)))\" (unable to call Sin \"sin\" with argument #0 Boolean \"1 = 1\" (expected INumber))")));
  EXPECT_THAT(
      [] { parseRawExpr("True/True"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"True/True\" (unable to call Div \"/\" with argument #0 Boolean \"True\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("((1 = 1)) + ((1 = 2))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((1 = 1)) + ((1 = 2))\" (unable to call AddOper \"+\" with argument #0 Boolean \"1 = 1\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("((1 = 1)) - ((1 = 1))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((1 = 1)) - ((1 = 1))\" (unable to call Sub \"-\" with argument #0 Boolean \"1 = 1\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("((1 = 1)) / ((1 = 1))"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"((1 = 1)) / ((1 = 1))\" (unable to call Div \"/\" with argument #0 Boolean \"1 = 1\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("(5+5)=(2=5)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(5+5)=(2=5)\" (unable to call Eqv \"=\" with argument #1 Boolean \"2 = 5\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("1+(sin(x)<2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1+(sin(x)<2)\" (unable to call AddOper \"+\" with argument #1 Boolean \"sin(x) < 2\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("1/(sin(x)<2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1/(sin(x)<2)\" (unable to call Div \"/\" with argument #1 Boolean \"sin(x) < 2\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("1+False"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1+False\" (unable to call AddOper \"+\" with argument #1 Boolean \"False\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("False+1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"False+1\" (unable to call AddOper \"+\" with argument #0 Boolean \"False\" (expected IArithmetic))")));
  EXPECT_THAT(
      [] { parseRawExpr("1=False"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1=False\" (unable to call Eqv \"=\" with argument #1 Boolean \"False\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("False=1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"False=1\" (unable to call Eqv \"=\" with argument #0 Boolean \"False\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("1&2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"1&2\" (unable to call AndOper \"&\" with argument #0 Integer \"1\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("E&I"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"E&I\" (unable to call AndOper \"&\" with argument #0 Real \"E\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("x+1&x+2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"x+1&x+2\" (unable to call AndOper \"&\" with argument #0 IArithmetic \"x + 1\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("x+1&x"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"x+1&x\" (unable to call AndOper \"&\" with argument #0 IArithmetic \"x + 1\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("x&x+2"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"x&x+2\" (unable to call AndOper \"&\" with argument #1 IArithmetic \"x + 2\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("(x&y)=(y&z)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(x&y)=(y&z)\" (unable to call Eqv \"=\" with argument #0 Boolean \"x & y\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("derivative(x=y, x)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"derivative(x=y, x)\" (unable to call Derivative \"derivative\" with argument #0 Boolean \"x = y\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("derivative(x&y,x)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"derivative(x&y,x)\" (unable to call Derivative \"derivative\" with argument #0 Boolean \"x & y\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("derivative(True,a)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"derivative(True,a)\" (unable to call Derivative \"derivative\" with argument #0 Boolean \"True\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("(a+1)_(a>2)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(a+1)_(a>2)\" (unable to call Index \"_\" with argument #0 IArithmetic \"a + 1\" (expected Variable))")));
  EXPECT_THAT(
      [] { parseRawExpr("(x+1)_1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(x+1)_1\" (unable to call Index \"_\" with argument #0 IArithmetic \"x + 1\" (expected Variable))")));
  EXPECT_THAT(
      [] { parseRawExpr("(x*2)_1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(x*2)_1\" (unable to call Index \"_\" with argument #0 IArithmetic \"x 2\" (expected Variable))")));
  EXPECT_THAT(
      [] { parseRawExpr("(x*2)_((x+2)_x)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"(x*2)_((x+2)_x)\" (unable to call Index \"_\" with argument #0 IArithmetic \"x + 2\" (expected Variable))")));
  EXPECT_THAT(
      [] { parseRawExpr("x^x_1"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"x^x_1\" (unable to call Index \"_\" with argument #0 INumber \"x^x\" (expected Variable))")));
  EXPECT_THAT(
      [] { parseRawExpr("E&a"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"E&a\" (unable to call AndOper \"&\" with argument #0 Real \"E\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("~Inf"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"~Inf\" (unable to call Not \"~\" with argument #0 INumber \"Inf\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("~Undefined"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"~Undefined\" (unable to call Not \"~\" with argument #0 IArithmetic \"Undefined\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("a | Undefined"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"a | Undefined\" (unable to call OrOper \"|\" with argument #1 IArithmetic \"Undefined\" (expected Boolean))")));
  EXPECT_THAT(
      [] { parseRawExpr("min()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"min()\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("min(True)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"min(True)\" (unable to call Min \"min\" with argument #0 Boolean \"True\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("min(True, False)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"min(True, False)\" (unable to call Min \"min\" with argument #0 Boolean \"True\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("max()"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"max()\" (incomplete expression inside brackets)")));
  EXPECT_THAT(
      [] { parseRawExpr("max(True)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"max(True)\" (unable to call Max \"max\" with argument #0 Boolean \"True\" (expected IComparable))")));
  EXPECT_THAT(
      [] { parseRawExpr("max(True, False)"); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq("Unable to parse an expression from \"max(True, False)\" (unable to call Max \"max\" with argument #0 Boolean \"True\" (expected IComparable))")));
}
