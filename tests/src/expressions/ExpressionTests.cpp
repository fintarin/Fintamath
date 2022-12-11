#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/EqvExpression.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionTests, EqvExpressionTest) {
  EXPECT_EQ(Expression("a+5<3").toString(), "a+5<3");
}

TEST(ExpressionTests, toStringTest) {
  EXPECT_EQ(Expression("a^-3").toString(), "a^(-3)");
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

TEST(ExpressionTests, stingConstructorTest) {
  // EXPECT_EQ(Expression("2").toString(), "2");
  // EXPECT_EQ(Expression("2 + 2").toString(), "4");
  // EXPECT_EQ(Expression("-2 + 3").toString(), "1");
  // EXPECT_EQ(Expression("2 * 2").toString(), "4");
  // EXPECT_EQ(Expression("1 / 3").toString(), "1/3");
  // EXPECT_EQ(Expression("0 / 3").toString(), "0");
  // EXPECT_EQ(Expression("2 ^ 2").toString(), "4");

  // EXPECT_EQ(Expression("0^1").toString(), "0");
  // EXPECT_EQ(Expression("2^0").toString(), "1");
  // EXPECT_EQ(Expression("(-7)^10").toString(), "282475249");
  // EXPECT_EQ(Expression("2^0").toString(), "1");

  // EXPECT_EQ(Expression("0.001-0.002").toString(), "-1/1000");
  // EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").toString(), "1");

  // EXPECT_EQ(Expression("2 + 2 * 2").toString(), "6");
  // EXPECT_EQ(Expression("2^2^2^2").toString(), "65536");
  // EXPECT_EQ(Expression("(2 + 2) * 2").toString(), "8");
  // EXPECT_EQ(Expression("(2-2)").toString(), "0");
  // EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(), "4");
  // EXPECT_EQ(Expression("((((2))))").toString(), "2");
  // EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(), "12");
  // EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(), "16");

  // EXPECT_EQ(Expression("--5").toString(), "5");
  // EXPECT_EQ(Expression("5*-3").toString(), "-15");

  // EXPECT_EQ(Expression("5!").simplify()->toString(), "120");
  // EXPECT_EQ(Expression("-1!").simplify()->toString(), "-1");
  // EXPECT_EQ(Expression("-100!").simplify()->toString(),
  //           "-933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536"
  //           "97920827223758251185210916864000000000000000000000000");
  // EXPECT_EQ(Expression("5!!").simplify()->toString(), "15");

  // EXPECT_EQ(Expression("(2)!").simplify()->toString(), "2");

  // EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(), "a");
  // EXPECT_EQ(Expression("a+a").toString(), "2*a");
  // EXPECT_EQ(Expression("a-a").toString(), "0");
  // EXPECT_EQ(Expression("(a+b)-b").toString(), "a");
  // EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(), "b^2+a^2+3*a*b");

  // EXPECT_EQ(Expression("lncossina").toString(), "ln(cos(sin(a)))");
  // EXPECT_EQ(Expression("(a+b)*(a+b)/(a+b)").toString(), "a+b");

  // EXPECT_EQ(Expression("+5").toString(), "5");
  // EXPECT_EQ(Expression("+a").toString(), "a");
  // EXPECT_EQ(Expression("a=a").toString(), "1");
  // EXPECT_EQ(Expression("a+a=2*a").toString(), "1");
  // EXPECT_EQ(Expression("(a+b)^2").toString(), "b^2+a^2+2*a*b");
}

TEST(ExpressionTests, simplifyTest) {
  // EXPECT_EQ(Expression("e ").simplify()->toString(), "2.718281828459045235360287471352662498");
  // EXPECT_EQ(Expression("pi").simplify()->toString(), "3.141592653589793238462643383279502884");

  // EXPECT_EQ(Expression("abs(-5)").simplify()->toString(), "5");
  // EXPECT_EQ(Expression("abs((-5))").simplify()->toString(), "5");

  // EXPECT_EQ(Expression("sqrt144").simplify()->toString(), "12");
  // EXPECT_EQ(Expression("sqrt0").simplify()->toString(), "0");
  // EXPECT_EQ(Expression("exp100").simplify()->toString(),
  //           "26881171418161354484126255515800135873611118.773741922415191608615280286685285277");

  // EXPECT_EQ(Expression("e^101").simplify()->toString(),
  //           "73070599793680672726476826340615135890078390.083960707616445859670987727649317305");
  // EXPECT_EQ(Expression("e^(-101)").simplify()->toString(), "0");

  // EXPECT_EQ(Expression("log(e,e)").simplify()->toString(), "1");
  // EXPECT_EQ(Expression("log(2, 256)").simplify()->toString(), "8");
  // EXPECT_EQ(Expression("log(pi, pi^10)").simplify()->toString(), "10");
  // EXPECT_EQ(Expression("log(e,e^3)").simplify()->toString(), "3");

  // EXPECT_EQ(Expression("ln3").simplify()->toString(), "1.098612288668109691395245236922525705");
  // EXPECT_EQ(Expression("ln2").simplify()->toString(), "0.693147180559945309417232121458176568");
  // EXPECT_EQ(Expression("ln100").simplify()->toString(), "4.605170185988091368035982909368728415");
  // EXPECT_EQ(Expression("ln(e)").simplify()->toString(), "1");

  // EXPECT_EQ(Expression("lg99").simplify()->toString(), "1.99563519459754991534025577775325486");
  // EXPECT_EQ(Expression("lg100").simplify()->toString(), "2");

  // EXPECT_EQ(Expression("lb100").simplify()->toString(), "6.643856189774724695740638858978780352");
  // EXPECT_EQ(Expression("lb4").simplify()->toString(), "2");

  // EXPECT_EQ(Expression("sin10").simplify()->toString(), "-0.544021110889369813404747661851377282");
  // EXPECT_EQ(Expression("cos10").simplify()->toString(), "-0.839071529076452452258863947824064835");
  // EXPECT_EQ(Expression("tan10").simplify()->toString(), "0.648360827459086671259124933009808677");
  // EXPECT_EQ(Expression("cot10").simplify()->toString(), "1.542351045356920048277469355682429311");

  // EXPECT_EQ(Expression("asin0.9").simplify()->toString(), "1.119769514998634186686677055845399616");
  // EXPECT_EQ(Expression("acos0.9").simplify()->toString(), "0.451026811796262432544644635794351826");
  // EXPECT_EQ(Expression("atan10").simplify()->toString(), "1.471127674303734591852875571761730852");
  // EXPECT_EQ(Expression("acot10").simplify()->toString(), "0.09966865249116202737844611987802059");

  // EXPECT_EQ(Expression("((2))*sqrt2").simplify()->toString(), "2.828427124746190097603377448419396157");
  // EXPECT_EQ(Expression("sqrt2*((2))").simplify()->toString(), "2.828427124746190097603377448419396157");

  // EXPECT_EQ(Expression("sin(1)^2").simplify()->toString(), "0.708073418273571193498784114750381095");
  // EXPECT_EQ(Expression("sin(-1)^2").simplify()->toString(), "0.708073418273571193498784114750381095");
  // EXPECT_EQ(Expression("sin1^2").simplify()->toString(), "0.708073418273571193498784114750381095");
  // EXPECT_EQ(Expression("sin(10^30)").simplify()->toString(), "-0.09011690191213805803038642895298733");
  // EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").simplify()->toString(), "1");
  // EXPECT_EQ(Expression("sin(pi/3)").simplify()->toString(), "0.866025403784438646763723170752936183");
  // EXPECT_EQ(Expression("cos(pi/3)").simplify()->toString(), "0.5");

  // EXPECT_EQ(Expression("lne").simplify()->toString(), "1");
  // EXPECT_EQ(Expression("lncossine").simplify()->toString(), "-0.086855992785406199870464541502090651");

  // EXPECT_EQ(Expression("e^101-e^101").simplify()->toString(), "0");
  // EXPECT_EQ(Expression("ln(e^e) / ln(e^e) - 1").simplify()->toString(), "0");

  // EXPECT_EQ(Expression("sqrt4!").simplify()->toString(), "2");
  // EXPECT_EQ(Expression("(sqrt4)!").simplify()->toString(), "2");
  // EXPECT_EQ(Expression("sqrt4*2!").simplify()->toString(), "4");
  // EXPECT_EQ(Expression("2!*e").simplify()->toString(), "5.436563656918090470720574942705324996");
  // EXPECT_EQ(Expression("e*2!").simplify()->toString(), "5.436563656918090470720574942705324996");

  // EXPECT_EQ(Expression("sqrt((1-cos(2*(pi/3)))/2)").simplify()->toString(),
  // "0.866025403784438646763723170752936183");
  // EXPECT_EQ(Expression("2*sqrt((1-cos(2*(pi/3)))/2)*cos(pi/3)").simplify()->toString(),
  //           "0.866025403784438646763723170752936183");
}

TEST(ExpressionTests, negativeTests) {
  // EXPECT_ANY_THROW(Expression(""));
  // EXPECT_ANY_THROW(Expression("1+"));
  // EXPECT_ANY_THROW(Expression("1-"));
  // EXPECT_ANY_THROW(Expression("1*"));
  // EXPECT_ANY_THROW(Expression("1/"));
  // EXPECT_ANY_THROW(Expression(" +   "));
  // EXPECT_ANY_THROW(Expression("(1+2))"));
  // EXPECT_ANY_THROW(Expression("5-*3"));
  // EXPECT_ANY_THROW(Expression("((()()))"));
  // EXPECT_ANY_THROW(Expression("2.a"));
  // EXPECT_ANY_THROW(Expression("2.2.2"));
  // EXPECT_ANY_THROW(Expression("sin"));
  // EXPECT_ANY_THROW(Expression("cos"));
  // EXPECT_ANY_THROW(Expression("log"));
  // EXPECT_ANY_THROW(Expression("ln"));
  // EXPECT_ANY_THROW(Expression("--"));
  // EXPECT_ANY_THROW(Expression("."));
  // EXPECT_ANY_THROW(Expression(","));
  // EXPECT_ANY_THROW(Expression("/"));
  // EXPECT_ANY_THROW(Expression(";"));
  // EXPECT_ANY_THROW(Expression("\'"));
  // EXPECT_ANY_THROW(Expression("["));
  // EXPECT_ANY_THROW(Expression("]"));
  // EXPECT_ANY_THROW(Expression("!"));
  // EXPECT_ANY_THROW(Expression("@"));
  // EXPECT_ANY_THROW(Expression("\""));
  // EXPECT_ANY_THROW(Expression("#"));
  // EXPECT_ANY_THROW(Expression("№"));
  // EXPECT_ANY_THROW(Expression("%"));
  // EXPECT_ANY_THROW(Expression(":"));
  // EXPECT_ANY_THROW(Expression("?"));
  // EXPECT_ANY_THROW(Expression("*"));
  // EXPECT_ANY_THROW(Expression("("));
  // EXPECT_ANY_THROW(Expression(")"));
  // EXPECT_ANY_THROW(Expression("-"));
  // EXPECT_ANY_THROW(Expression("+"));
  // EXPECT_ANY_THROW(Expression("$"));
  // EXPECT_ANY_THROW(Expression("^"));
  // EXPECT_ANY_THROW(Expression("&"));
  // EXPECT_ANY_THROW(Expression("_"));
  // EXPECT_ANY_THROW(Expression("[1+1]"));
  // EXPECT_ANY_THROW(Expression("{1}"));
  // EXPECT_ANY_THROW(Expression("(1"));
  // EXPECT_ANY_THROW(Expression("(((2)"));
  // EXPECT_ANY_THROW(Expression("(((2))"));
  // EXPECT_ANY_THROW(Expression("((2)))"));
  // EXPECT_ANY_THROW(Expression("(2)))"));
  // EXPECT_ANY_THROW(Expression("(2"));
  // EXPECT_ANY_THROW(Expression("((2)"));
  // EXPECT_ANY_THROW(Expression("((2"));
  // EXPECT_ANY_THROW(Expression("(()())"));
  // EXPECT_ANY_THROW(Expression("((((()))))"));
  // EXPECT_ANY_THROW(Expression("((((2)((2))))"));
  // EXPECT_ANY_THROW(Expression("!2"));
  // EXPECT_ANY_THROW(Expression("!!2"));
  // EXPECT_ANY_THROW(Expression("!2!!"));
  // EXPECT_ANY_THROW(Expression("!(2"));
  // EXPECT_ANY_THROW(Expression("!(2)"));
  // EXPECT_ANY_THROW(Expression("2)!"));
  // EXPECT_ANY_THROW(Expression("1/0"));
  // EXPECT_ANY_THROW(Expression("0^0"));
  // EXPECT_ANY_THROW(Expression("sin(2))!"));

  // EXPECT_ANY_THROW(Expression("(-1)!").simplify());
  // EXPECT_ANY_THROW(Expression("(2/3)!").simplify());
  // EXPECT_ANY_THROW(Expression("(-1)!!").simplify());
  // EXPECT_ANY_THROW(Expression("(2/3)!!").simplify());
  // EXPECT_ANY_THROW(Expression("e!").simplify());
  // EXPECT_ANY_THROW(Expression("sqrt(-1)").simplify());
  // EXPECT_ANY_THROW(Expression("ln(0)").simplify());
  // EXPECT_ANY_THROW(Expression("ln(-1)").simplify());
  // EXPECT_ANY_THROW(Expression("log(-1, 1)").simplify());
  // EXPECT_ANY_THROW(Expression("log(0, 1)").simplify());
  // EXPECT_ANY_THROW(Expression("log(1, 0)").simplify());
  // EXPECT_ANY_THROW(Expression("lb(-1)").simplify());
  // EXPECT_ANY_THROW(Expression("lg(-1)").simplify());
  // EXPECT_ANY_THROW(Expression("(-1)^(2/3)").simplify());
  // EXPECT_ANY_THROW(Expression("tan(pi/2)").simplify());
  // EXPECT_ANY_THROW(Expression("cot(0)").simplify());
  // EXPECT_ANY_THROW(Expression("asin(2)").simplify());
  // EXPECT_ANY_THROW(Expression("acos(2)").simplify());
  // EXPECT_ANY_THROW(Expression("tan(3/2*pi)").simplify());
  // EXPECT_ANY_THROW(Expression("cot(2*pi)").simplify());

  // EXPECT_ANY_THROW(
  //     Expression("1-2*sin((pi/6))*sqrt((1/2)*(1-1-2*sin((pi/6))*sqrt((1/2)*(1-cos(2(pi/6))))))").simplify());
}
