// #include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/Functions.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/literals/Variable.hpp"

// #include <fstream>

// using namespace fintamath;

// TEST(ExpressionTests, constructorTest) {
//   EXPECT_EQ(Expression().toString(), "0");
// }

// TEST(ExpressionTests, moveTest) {
//   auto a = Expression("1+2");
//   EXPECT_EQ(a.toString(), "3");
//   auto b = std::move(a);
//   EXPECT_TRUE(b.toString() == "3" && a.toString() == "0");
//   a = std::move(b);
//   EXPECT_TRUE(a.toString() == "3" && b.toString() == "0");
// }

// TEST(ExpressionTests, copyTest) {
//   auto a = Expression("1+2");
//   auto b = a;
//   EXPECT_TRUE(a == b && &a != &b);
// }

TEST(ExpressionTests, testTest) {
  auto a = Expression("3/a");
  auto b = a.toString();
}

TEST(ExpressionTests, stingConstructorTest) {
  EXPECT_EQ(Expression("2").toString(), "2");
  EXPECT_EQ(Expression("2 + 2").toString(), "4");
  EXPECT_EQ(Expression("-2 + 3").toString(), "1");
  EXPECT_EQ(Expression("2 * 2").toString(), "4");
  EXPECT_EQ(Expression("1 / 3").toString(), "1/3");
  EXPECT_EQ(Expression("0 / 3").toString(), "0");
  EXPECT_EQ(Expression("2 ^ 2").toString(), "4");

//   EXPECT_EQ(Expression("0^1").toString(), "0");
//   EXPECT_EQ(Expression("2^0").toString(), "1");
//   EXPECT_EQ(Expression("(-7)^10").toString(), "282475249");
//   EXPECT_EQ(Expression("2^0").toString(), "1");

//   EXPECT_EQ(Expression("0.001-0.002").toString(), "-1/1000");
//   EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").toString(), "1");

//   EXPECT_EQ(Expression("2 + 2 * 2").toString(), "6");
//   EXPECT_EQ(Expression("2^2^2^2").toString(), "65536");
//   EXPECT_EQ(Expression("(2 + 2) * 2").toString(), "8");
//   EXPECT_EQ(Expression("(2-2)").toString(), "0");
//   EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(), "4");
//   EXPECT_EQ(Expression("((((2))))").toString(), "2");
//   EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(), "12");
//   EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(), "16");

//   EXPECT_EQ(Expression("--5").toString(), "5");
//   EXPECT_EQ(Expression("5*-3").toString(), "-15");

//   EXPECT_EQ(Expression("5!").toString(), "120");
//   EXPECT_EQ(Expression("-1!").toString(), "-1");
//   EXPECT_EQ(Expression("-100!").toString(),
//             "-933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536"
//             "97920827223758251185210916864000000000000000000000000");
//   EXPECT_EQ(Expression("5!!").toString(), "15");

//   EXPECT_EQ(Expression("(2)!").toString(), "2");

//   EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(), "a");
//   EXPECT_EQ(Expression("a+a").toString(), "2*a");
//   EXPECT_EQ(Expression("a-a").toString(), "0");
//   EXPECT_EQ(Expression("(a+b)-b").toString(), "a");
//   EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(), "b^2+a^2+3*a*b");

  EXPECT_EQ(Expression("ln cos sin a").toString(), "ln(cos(sin(a)))");
  EXPECT_EQ(Expression("(a+b)*(a+b)/(a+b)").toString(), "a+b");

//   EXPECT_EQ(Expression("+5").toString(), "5");
//   EXPECT_EQ(Expression("+a").toString(), "a");
//   EXPECT_EQ(Expression("a=a").toString(), "1");
//   EXPECT_EQ(Expression("a+a=2*a").toString(), "1");
//   EXPECT_EQ(Expression("(a+b)^2").toString(), "b^2+a^2+2*a*b");

//   EXPECT_EQ(Expression("e ").toString(), "2.718281828459045235360287471352662498");
//   EXPECT_EQ(Expression("pi").toString(), "3.141592653589793238462643383279502884");

//   EXPECT_EQ(Expression("abs(-5)").toString(), "5");
//   EXPECT_EQ(Expression("abs((-5))").toString(), "5");

//   EXPECT_EQ(Expression("sqrt144").toString(), "12");
//   EXPECT_EQ(Expression("sqrt0").toString(), "0");
//   EXPECT_EQ(Expression("exp100").toString(),
//             "26881171418161354484126255515800135873611118.773741922415191608615280286685285277");

//   EXPECT_EQ(Expression("e^101").toString(),
//             "73070599793680672726476826340615135890078390.083960707616445859670987727649317305");
//   EXPECT_EQ(Expression("e^(-101)").toString(), "0");

//   EXPECT_EQ(Expression("log(e,e)").toString(), "1");
//   EXPECT_EQ(Expression("log(2, 256)").toString(), "8");
//   EXPECT_EQ(Expression("log(pi, pi^10)").toString(), "10");
//   EXPECT_EQ(Expression("log(e,e^3)").toString(), "3");

//   EXPECT_EQ(Expression("ln3").toString(), "1.098612288668109691395245236922525705");
//   EXPECT_EQ(Expression("ln2").toString(), "0.693147180559945309417232121458176568");
//   EXPECT_EQ(Expression("ln100").toString(), "4.605170185988091368035982909368728415");
//   EXPECT_EQ(Expression("ln(e)").toString(), "1");

//   EXPECT_EQ(Expression("lg99").toString(), "1.99563519459754991534025577775325486");
//   EXPECT_EQ(Expression("lg100").toString(), "2");

//   EXPECT_EQ(Expression("lb100").toString(), "6.643856189774724695740638858978780352");
//   EXPECT_EQ(Expression("lb4").toString(), "2");

//   EXPECT_EQ(Expression("sin10").toString(), "-0.544021110889369813404747661851377282");
//   EXPECT_EQ(Expression("cos10").toString(), "-0.839071529076452452258863947824064835");
//   EXPECT_EQ(Expression("tan10").toString(), "0.648360827459086671259124933009808677");
//   EXPECT_EQ(Expression("cot10").toString(), "1.542351045356920048277469355682429311");

//   EXPECT_EQ(Expression("asin0.9").toString(), "1.119769514998634186686677055845399616");
//   EXPECT_EQ(Expression("acos0.9").toString(), "0.451026811796262432544644635794351826");
//   EXPECT_EQ(Expression("atan10").toString(), "1.471127674303734591852875571761730852");
//   EXPECT_EQ(Expression("acot10").toString(), "0.09966865249116202737844611987802059");

//   EXPECT_EQ(Expression("((2))*sqrt2").toString(), "2.828427124746190097603377448419396157");
//   EXPECT_EQ(Expression("sqrt2*((2))").toString(), "2.828427124746190097603377448419396157");

//   EXPECT_EQ(Expression("sin(1)^2").toString(), "0.708073418273571193498784114750381095");
//   EXPECT_EQ(Expression("sin(-1)^2").toString(), "0.708073418273571193498784114750381095");
//   EXPECT_EQ(Expression("sin1^2").toString(), "0.708073418273571193498784114750381095");
//   EXPECT_EQ(Expression("sin(10^30)").toString(), "-0.09011690191213805803038642895298733");
//   EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").toString(), "1");
//   EXPECT_EQ(Expression("sin(pi/3)").toString(), "0.866025403784438646763723170752936183");
//   EXPECT_EQ(Expression("cos(pi/3)").toString(), "0.5");

//   EXPECT_EQ(Expression("lne").toString(), "1");
//   EXPECT_EQ(Expression("lncossine").toString(), "-0.086855992785406199870464541502090651");

//   EXPECT_EQ(Expression("e^101-e^101").toString(), "0");
//   EXPECT_EQ(Expression("ln(e^e) / ln(e^e) - 1").toString(), "0");

//   EXPECT_EQ(Expression("sqrt4!").toString(), "2");
//   EXPECT_EQ(Expression("(sqrt4)!").toString(), "2");
//   EXPECT_EQ(Expression("sqrt4*2!").toString(), "4");
//   EXPECT_EQ(Expression("2!*e").toString(), "5.436563656918090470720574942705324996");
//   EXPECT_EQ(Expression("e*2!").toString(), "5.436563656918090470720574942705324996");

//   EXPECT_EQ(Expression("sqrt((1-cos(2*(pi/3)))/2)").toString(), "0.866025403784438646763723170752936183");
//   EXPECT_EQ(Expression("2*sqrt((1-cos(2*(pi/3)))/2)*cos(pi/3)").toString(), "0.866025403784438646763723170752936183");
// }

// TEST(ExpressionTests, stringConstructorNegativeTest) {
//   EXPECT_ANY_THROW(Expression(""));
//   EXPECT_ANY_THROW(Expression("1+"));
//   EXPECT_ANY_THROW(Expression("1-"));
//   EXPECT_ANY_THROW(Expression("1*"));
//   EXPECT_ANY_THROW(Expression("1/"));
//   EXPECT_ANY_THROW(Expression(" +   "));
//   EXPECT_ANY_THROW(Expression("(1+2))"));
//   EXPECT_ANY_THROW(Expression("5-*3"));
//   EXPECT_ANY_THROW(Expression("((()()))"));
//   EXPECT_ANY_THROW(Expression("2.a"));
//   EXPECT_ANY_THROW(Expression("2.2.2"));
//   EXPECT_ANY_THROW(Expression("sin"));
//   EXPECT_ANY_THROW(Expression("cos"));
//   EXPECT_ANY_THROW(Expression("log"));
//   EXPECT_ANY_THROW(Expression("ln"));
//   EXPECT_ANY_THROW(Expression("--"));
//   EXPECT_ANY_THROW(Expression("."));
//   EXPECT_ANY_THROW(Expression(","));
//   EXPECT_ANY_THROW(Expression("/"));
//   EXPECT_ANY_THROW(Expression(";"));
//   EXPECT_ANY_THROW(Expression("\'"));
//   EXPECT_ANY_THROW(Expression("["));
//   EXPECT_ANY_THROW(Expression("]"));
//   EXPECT_ANY_THROW(Expression("!"));
//   EXPECT_ANY_THROW(Expression("@"));
//   EXPECT_ANY_THROW(Expression("\""));
//   EXPECT_ANY_THROW(Expression("#"));
//   EXPECT_ANY_THROW(Expression("№"));
//   EXPECT_ANY_THROW(Expression("%"));
//   EXPECT_ANY_THROW(Expression(":"));
//   EXPECT_ANY_THROW(Expression("?"));
//   EXPECT_ANY_THROW(Expression("*"));
//   EXPECT_ANY_THROW(Expression("("));
//   EXPECT_ANY_THROW(Expression(")"));
//   EXPECT_ANY_THROW(Expression("-"));
//   EXPECT_ANY_THROW(Expression("+"));
//   EXPECT_ANY_THROW(Expression("$"));
//   EXPECT_ANY_THROW(Expression("^"));
//   EXPECT_ANY_THROW(Expression("&"));
//   EXPECT_ANY_THROW(Expression("_"));
//   EXPECT_ANY_THROW(Expression("[1+1]"));
//   EXPECT_ANY_THROW(Expression("{1}"));
//   EXPECT_ANY_THROW(Expression("(1"));
//   EXPECT_ANY_THROW(Expression("(((2)"));
//   EXPECT_ANY_THROW(Expression("(((2))"));
//   EXPECT_ANY_THROW(Expression("((2)))"));
//   EXPECT_ANY_THROW(Expression("(2)))"));
//   EXPECT_ANY_THROW(Expression("(2"));
//   EXPECT_ANY_THROW(Expression("((2)"));
//   EXPECT_ANY_THROW(Expression("((2"));
//   EXPECT_ANY_THROW(Expression("(()())"));
//   EXPECT_ANY_THROW(Expression("((((()))))"));
//   EXPECT_ANY_THROW(Expression("((((2)((2))))"));
//   EXPECT_ANY_THROW(Expression("!2"));
//   EXPECT_ANY_THROW(Expression("!!2"));
//   EXPECT_ANY_THROW(Expression("!2!!"));
//   EXPECT_ANY_THROW(Expression("!(2"));
//   EXPECT_ANY_THROW(Expression("!(2)"));
//   EXPECT_ANY_THROW(Expression("2)!"));
//   EXPECT_ANY_THROW(Expression("1/0"));
//   EXPECT_ANY_THROW(Expression("0^0"));
//   EXPECT_ANY_THROW(Expression("sin(2))!"));

//   EXPECT_ANY_THROW(Expression("(-1)!"));
//   EXPECT_ANY_THROW(Expression("(2/3)!"));
//   EXPECT_ANY_THROW(Expression("(-1)!!"));
//   EXPECT_ANY_THROW(Expression("(2/3)!!"));
//   EXPECT_ANY_THROW(Expression("e!"));
//   EXPECT_ANY_THROW(Expression("sqrt(-1)"));
//   EXPECT_ANY_THROW(Expression("ln(0)"));
//   EXPECT_ANY_THROW(Expression("ln(-1)"));
//   EXPECT_ANY_THROW(Expression("log(-1, 1)"));
//   EXPECT_ANY_THROW(Expression("log(0, 1)"));
//   EXPECT_ANY_THROW(Expression("log(1, 0)"));
//   EXPECT_ANY_THROW(Expression("lb(-1)"));
//   EXPECT_ANY_THROW(Expression("lg(-1)"));
//   EXPECT_ANY_THROW(Expression("(-1)^(2/3)"));
//   EXPECT_ANY_THROW(Expression("tan(pi/2)"));
//   EXPECT_ANY_THROW(Expression("cot(0)"));
//   EXPECT_ANY_THROW(Expression("asin(2)"));
//   EXPECT_ANY_THROW(Expression("acos(2)"));
//   EXPECT_ANY_THROW(Expression("tan(3/2*pi)"));
//   EXPECT_ANY_THROW(Expression("cot(2*pi)"));

//   EXPECT_ANY_THROW(Expression("1-2*sin((pi/6))*sqrt((1/2)*(1-1-2*sin((pi/6))*sqrt((1/2)*(1-cos(2(pi/6))))))"));
// }

// TEST(ExpressionTests, solveTest) {
// }

// TEST(ExpressionTests, toStringTest) {
//   EXPECT_EQ(Expression("a^-3").toString(), "a^(-3)");
// }
