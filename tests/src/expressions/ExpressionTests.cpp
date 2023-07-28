#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

#include <fstream>

using namespace fintamath;

TEST(ExpressionTests, constructorTest) {
  EXPECT_EQ(Expression().toString(), "0");
}

TEST(ExpressionTests, moveTest) {
  auto a = Expression("1+2");
  EXPECT_EQ(a.toString(), "3");

  auto b = std::move(a);
  EXPECT_TRUE(b.toString() == "3" && &a != &b);

  a = std::move(b);
  EXPECT_TRUE(a.toString() == "3" && &a != &b);
}

TEST(ExpressionTests, copyTest) {
  auto a = Expression("1+2");
  auto b = a;
  EXPECT_TRUE(a == b && &a != &b);
}

TEST(ExpressionTests, stringConstructorTest) {
  EXPECT_EQ(Expression("2").toString(), "2");
  EXPECT_EQ(Expression("2 + 2").toString(), "4");
  EXPECT_EQ(Expression(" 2 + 2 ").toString(), "4");
  EXPECT_EQ(Expression("-2 + 3").toString(), "1");
  EXPECT_EQ(Expression("2 * 2").toString(), "4");
  EXPECT_EQ(Expression("-2 * 2").toString(), "-4");
  EXPECT_EQ(Expression("2 * -2").toString(), "-4");
  EXPECT_EQ(Expression("2 * 3!").toString(), "12");
  EXPECT_EQ(Expression("1 / 3").toString(), "1/3");
  EXPECT_EQ(Expression("0 / 3").toString(), "0");
  EXPECT_EQ(Expression("2 ^ 2").toString(), "4");
  EXPECT_EQ(Expression("-2 ^ 2").toString(), "-4");
  EXPECT_EQ(Expression("2 ^ -2").toString(), "1/4");
  EXPECT_EQ(Expression("2 ^ 3!").toString(), "64");
  EXPECT_EQ(Expression("0^1").toString(), "0");
  EXPECT_EQ(Expression("2^0").toString(), "1");
  EXPECT_EQ(Expression("(-7)^10").toString(), "282475249");
  EXPECT_EQ(Expression("2^0").toString(), "1");
  EXPECT_EQ(Expression("0.001-0.002").toString(), "-1/1000");
  EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").toString(), "1");
  EXPECT_EQ(Expression("2 + 2 * 2").toString(), "6");
  EXPECT_EQ(Expression("2^2^2^2").toString(), "256");
  EXPECT_EQ(Expression("(2 + 2) * 2").toString(), "8");
  EXPECT_EQ(Expression("(2-2)").toString(), "0");
  EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(), "4");
  EXPECT_EQ(Expression("((((2))))").toString(), "2");
  EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(), "12");
  EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(), "16");
  EXPECT_EQ(Expression("-5").toString(), "-5");
  EXPECT_EQ(Expression("--5").toString(), "5");
  EXPECT_EQ(Expression("---5").toString(), "-5");
  EXPECT_EQ(Expression("+5").toString(), "5");
  EXPECT_EQ(Expression("5*-3").toString(), "-15");
  EXPECT_EQ(Expression("----5+++5").toString(), "10");
  EXPECT_EQ(Expression("5----4").toString(), "9");
  EXPECT_EQ(Expression("5+-+-4").toString(), "9");
  EXPECT_EQ(Expression("5*+++---4").toString(), "-20");
  EXPECT_EQ(Expression("1^-1").toString(), "1");
  EXPECT_EQ(Expression("1.").toString(), "1");
  EXPECT_EQ(Expression(".1").toString(), "1/10");
  EXPECT_EQ(Expression("2+.1+.1+1.+1.").toString(), "21/5");
  EXPECT_EQ(Expression("1/10^-20").toString(), "100000000000000000000");
  EXPECT_EQ(Expression("1/10^--20").toString(), "1/100000000000000000000");
  EXPECT_EQ(Expression("1/10^---20").toString(), "100000000000000000000");
  EXPECT_EQ(Expression("36/3(8-6)").toString(), "24");
  EXPECT_EQ(Expression("36/(8-6)3").toString(), "54");
  EXPECT_EQ(Expression("2%").toString(), "1/50");
  EXPECT_EQ(Expression("2.35%").toString(), "47/2000");
  EXPECT_EQ(Expression("1100*4.76%").toString(), "1309/25");
  EXPECT_EQ(Expression("2.35%%%%").toString(), "47/2000000000");
  EXPECT_EQ(Expression("1100*4.76%1100*4.76%").toString(), "1713481/625");
  EXPECT_EQ(Expression("((((((5)/(8)))/(1)))/(((((((9)/(4)))/(0)))/(5))))").toString(), "0");

  EXPECT_EQ(Expression("9!").toString(), "362880");
  EXPECT_EQ(Expression("-1!").toString(), "-1");
  EXPECT_EQ(Expression("-100!").toString(),
            "-933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536"
            "97920827223758251185210916864000000000000000000000000");
  EXPECT_EQ(Expression("(5!)!").toString(),
            "6689502913449127057588118054090372586752746333138029810295671352301633557244962989366874165271984981308157"
            "637893214090552534408589408121859898481114389650005964960521256960000000000000000000000000000");
  EXPECT_EQ(Expression("(2)!").toString(), "2");

  EXPECT_EQ(Expression("5!").toString(), "120");
  EXPECT_EQ(Expression("5!!").toString(), "15");
  EXPECT_EQ(Expression("5!!!").toString(), "10");
  EXPECT_EQ(Expression("5!!!!").toString(), "5");
  EXPECT_EQ(Expression("5!!!!!").toString(), "5");
  EXPECT_EQ(Expression("5!!!!!!").toString(), "5");
  EXPECT_EQ(Expression("6!").toString(), "720");
  EXPECT_EQ(Expression("6!!").toString(), "48");
  EXPECT_EQ(Expression("6!!!").toString(), "18");
  EXPECT_EQ(Expression("6!!!!").toString(), "12");
  EXPECT_EQ(Expression("6!!!!!").toString(), "6");
  EXPECT_EQ(Expression("6!!!!!!").toString(), "6");
  EXPECT_EQ(Expression("15!!!!!!").toString(), "405");
  EXPECT_EQ(Expression("15!!!!!!!").toString(), "120");
  EXPECT_EQ(Expression("30!!!!!!").toString(), "933120");
  EXPECT_EQ(Expression("30!!!!!!!").toString(), "198720");

  EXPECT_EQ(Expression("sqrt144").toString(), "12");
  EXPECT_EQ(Expression("sqrt0").toString(), "0");
  EXPECT_EQ(Expression("sqrt(25)").toString(), "5");
  EXPECT_EQ(Expression("sqrt(144/25)").toString(), "12/5");
  EXPECT_EQ(Expression("sqrt(50)").toString(), "5 sqrt(2)");
  EXPECT_EQ(Expression("sqrt(26)").toString(), "sqrt(26)");
  EXPECT_EQ(Expression("sqrt(145/26)").toString(), "sqrt(145/26)");
  EXPECT_EQ(Expression("sqrt(169/3)").toString(), "13/sqrt(3)");
  EXPECT_EQ(Expression("sqrt(168/25)").toString(), "(2 sqrt(42))/5");
  EXPECT_EQ(Expression("root(4, 2)").toString(), "2");
  EXPECT_EQ(Expression("root(8, 3)").toString(), "2");
  EXPECT_EQ(Expression("root(16, 4)").toString(), "2");
  EXPECT_EQ(Expression("root(27, 3)").toString(), "3");
  EXPECT_EQ(Expression("4^(1/2)").toString(), "2");
  EXPECT_EQ(Expression("8^(1/3)").toString(), "2");
  EXPECT_EQ(Expression("8^(4/3)").toString(), "16");
  EXPECT_EQ(Expression("7 2^(2/3)").toString(), "7 root(4, 3)");
  EXPECT_EQ(Expression("2^(2/3) 3^(2/3)").toString(), "root(36, 3)");
  EXPECT_EQ(Expression("2^(2/3) 7^(2/3) 3^(3/4)").toString(), "root(196, 3) root(27, 4)");
  EXPECT_EQ(Expression("2^(2/3) 1/7^(2/3) 3^(3/4)").toString(), "root(4/49, 3) root(27, 4)");

  EXPECT_EQ(Expression("E").toString(), "E");
  EXPECT_EQ(Expression("Pi").toString(), "Pi");
  EXPECT_EQ(Expression("E^101-E^101").toString(), "0");
  EXPECT_EQ(Expression("ln(E^E) / ln(E^E) - 1").toString(), "0");
  EXPECT_EQ(Expression("8E").toString(), "8 E");
  EXPECT_EQ(Expression("8Pi").toString(), "8 Pi");
  EXPECT_EQ(Expression("E8").toString(), "8 E");
  EXPECT_EQ(Expression("Pi8").toString(), "8 Pi");
  EXPECT_EQ(Expression("exp100").toString(), "E^100");
  EXPECT_EQ(Expression("E^101").toString(), "E^101");
  EXPECT_EQ(Expression("E^(-101)").toString(), "1/(E^101)");
  EXPECT_EQ(Expression("log(E,E)").toString(), "1");
  EXPECT_EQ(Expression("log(Pi, Pi^10)").toString(), "10");
  EXPECT_EQ(Expression("log(E,E^3)").toString(), "3");
  EXPECT_EQ(Expression("log((Pi),(E)^((Pi)))").toString(), "Pi log(Pi, E)");
  EXPECT_EQ(Expression("log(E^3, E)").toString(), "1/3");
  EXPECT_EQ(Expression("log(E^Pi, E)").toString(), "1/Pi");
  EXPECT_EQ(Expression("ln3").toString(), "ln(3)");
  EXPECT_EQ(Expression("ln2").toString(), "ln(2)");
  EXPECT_EQ(Expression("ln100").toString(), "ln(100)");
  EXPECT_EQ(Expression("ln(E)").toString(), "1");
  EXPECT_EQ(Expression("lg99").toString(), "log(10, 99)");
  EXPECT_EQ(Expression("lg100").toString(), "2");
  EXPECT_EQ(Expression("lb100").toString(), "log(2, 100)");
  EXPECT_EQ(Expression("lb4").toString(), "2");
  EXPECT_EQ(Expression("ln(ln(E))").toString(), "0");
  EXPECT_EQ(Expression("ln(E)!").toString(), "1");
  EXPECT_EQ(Expression("sin10").toString(), "sin(10)");
  EXPECT_EQ(Expression("cos10").toString(), "cos(10)");
  EXPECT_EQ(Expression("tan10").toString(), "tan(10)");
  EXPECT_EQ(Expression("cot10").toString(), "cot(10)");
  EXPECT_EQ(Expression("asin0.9").toString(), "asin(9/10)");
  EXPECT_EQ(Expression("acos0.9").toString(), "acos(9/10)");
  EXPECT_EQ(Expression("atan10").toString(), "atan(10)");
  EXPECT_EQ(Expression("acot10").toString(), "acot(10)");
  EXPECT_EQ(Expression("sinh10").toString(), "sinh(10)");
  EXPECT_EQ(Expression("cosh10").toString(), "cosh(10)");
  EXPECT_EQ(Expression("tanh10").toString(), "tanh(10)");
  EXPECT_EQ(Expression("coth10").toString(), "coth(10)");
  EXPECT_EQ(Expression("asinh0.9").toString(), "asinh(9/10)");
  EXPECT_EQ(Expression("acosh1.9").toString(), "acosh(19/10)");
  EXPECT_EQ(Expression("atanh0.9").toString(), "atanh(9/10)");
  EXPECT_EQ(Expression("acoth1.9").toString(), "acoth(19/10)");
  EXPECT_EQ(Expression("((2))*sqrt2").toString(), "2 sqrt(2)");
  EXPECT_EQ(Expression("sqrt2*((2))").toString(), "2 sqrt(2)");
  EXPECT_EQ(Expression("sin(1)^2").toString(), "sin(1)^2");
  EXPECT_EQ(Expression("sin(-1)^2").toString(), "sin(-1)^2");
  EXPECT_EQ(Expression("sin1^2").toString(), "sin(1)^2");
  EXPECT_EQ(Expression("sin(10^30)").toString(), "sin(1000000000000000000000000000000)");
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").toString(), "cos(1)^2 + sin(1)^2");
  EXPECT_EQ(Expression("sin(Pi/3)").toString(), "sin(Pi/3)");
  EXPECT_EQ(Expression("cos(Pi/3)").toString(), "cos(Pi/3)");
  EXPECT_EQ(Expression("2!*E").toString(), "2 E");
  EXPECT_EQ(Expression("E*2!").toString(), "2 E");
  EXPECT_EQ(Expression("sqrt((1-cos(2*(Pi/3)))/2)").toString(), "sqrt(-cos((2 Pi)/3)/2 + 1/2)");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(Pi/3)))/2)*cos(Pi/3)").toString(), "2 sqrt(-cos((2 Pi)/3)/2 + 1/2) cos(Pi/3)");
  EXPECT_EQ(Expression("-sin(2)").toString(), "-sin(2)");
  EXPECT_EQ(Expression("log(2, 256)").toString(), "8");
  EXPECT_EQ(Expression("2^(3/2)").toString(), "2 sqrt(2)");
  EXPECT_EQ(Expression("sqrt(sqrt5)").toString(), "root(5, 4)");
  EXPECT_EQ(Expression("sqrt4!").toString(), "2");
  EXPECT_EQ(Expression("(sqrt4)!").toString(), "2");
  EXPECT_EQ(Expression("sqrt4*2!").toString(), "4");
  EXPECT_EQ(Expression("abs(-5)").toString(), "5");
  EXPECT_EQ(Expression("abs((-5))").toString(), "5");
  EXPECT_EQ(Expression("sign(10)").toString(), "1");
  EXPECT_EQ(Expression("sign(0)").toString(), "0");
  EXPECT_EQ(Expression("sign(-5)").toString(), "-1");
  EXPECT_EQ(Expression("frac(2,4)").toString(), "1/2");
  EXPECT_EQ(Expression("frac(x,y)").toString(), "x/y");
  EXPECT_EQ(Expression("pow(2,4)").toString(), "16");
  EXPECT_EQ(Expression("pow(x,y)").toString(), "x^y");
  EXPECT_EQ(Expression("1deg").toString(), "Pi/180");
  EXPECT_EQ(Expression("60deg").toString(), "Pi/3");
  EXPECT_EQ(Expression("adeg").toString(), "(Pi a)/180");

  EXPECT_EQ(Expression("a*0").toString(), "0");
  EXPECT_EQ(Expression("0*a").toString(), "0");
  EXPECT_EQ(Expression("1*a").toString(), "a");
  EXPECT_EQ(Expression("a*1").toString(), "a");

  EXPECT_EQ(Expression("0^a").toString(), "0");
  EXPECT_EQ(Expression("1^a").toString(), "1");
  EXPECT_EQ(Expression("(a b)^0").toString(), "1");
  EXPECT_EQ(Expression("(a + b)^-1").toString(), "1/(a + b)");
  EXPECT_EQ(Expression("(a + b)^-2").toString(), "1/(a^2 + 2 a b + b^2)");
  EXPECT_EQ(Expression("(a b)^-1").toString(), "1/(a b)");
  EXPECT_EQ(Expression("(a b)^-2").toString(), "1/(a^2 b^2)");

  EXPECT_EQ(Expression("2%a").toString(), "a/50");
  EXPECT_EQ(Expression("2!!!!a!!!").toString(), "2 a!!!");
  EXPECT_EQ(Expression("sin a").toString(), "sin(a)");
  EXPECT_EQ(Expression("s i n a").toString(), "a i n s");
  EXPECT_EQ(Expression("a(2)").toString(), "2 a");
  EXPECT_EQ(Expression("(2)a").toString(), "2 a");
  EXPECT_EQ(Expression("Ea").toString(), "E a");
  EXPECT_EQ(Expression("aE").toString(), "E a");
  EXPECT_EQ(Expression("aEE").toString(), "E^2 a");
  EXPECT_EQ(Expression("EEa").toString(), "E^2 a");
  EXPECT_EQ(Expression("x123").toString(), "123 x");
  EXPECT_EQ(Expression("lnE").toString(), "1");
  EXPECT_EQ(Expression("lncossinE").toString(), "ln(cos(sin(E)))");
  EXPECT_EQ(Expression("ln cos sin a").toString(), "ln(cos(sin(a)))");

  EXPECT_EQ(Expression("2.a").toString(), "2 a");
  EXPECT_EQ(Expression("a.2").toString(), "a/5");
  EXPECT_EQ(Expression("a+a").toString(), "2 a");
  EXPECT_EQ(Expression("a-a").toString(), "0");
  EXPECT_EQ(Expression("-a").toString(), "-a");
  EXPECT_EQ(Expression("+a").toString(), "a");
  EXPECT_EQ(Expression("--a").toString(), "a");
  EXPECT_EQ(Expression("---a").toString(), "-a");
  EXPECT_EQ(Expression("b--a").toString(), "a + b");
  EXPECT_EQ(Expression("b---a").toString(), "-a + b");
  EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(), "a");
  EXPECT_EQ(Expression("-(-(-(-(-(-(-(-(-a))))))))").toString(), "-a");
  EXPECT_EQ(Expression("--------a").toString(), "a");
  EXPECT_EQ(Expression("---------a").toString(), "-a");
  EXPECT_EQ(Expression("abcdefg").toString(), "a b c d e f g");
  EXPECT_EQ(Expression("a+b+c+d+e+f+g").toString(), "a + b + c + d + e + f + g");
  EXPECT_EQ(Expression("(a+b)-b").toString(), "a");
  EXPECT_EQ(Expression("a-b-c").toString(), "a - b - c");
  EXPECT_EQ(Expression("a-(b-c)").toString(), "a - b + c");
  EXPECT_EQ(Expression("(a-b)-c").toString(), "a - b - c");
  EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(), "a^2 + 3 a b + b^2");
  EXPECT_EQ(Expression("x/y/z").toString(), "x/(y z)");
  EXPECT_EQ(Expression("x/(y/z)").toString(), "(x z)/y");
  EXPECT_EQ(Expression("(x/y)/z").toString(), "x/(y z)");
  EXPECT_EQ(Expression("x^y^z").toString(), "x^(y z)");
  EXPECT_EQ(Expression("x^(y^z)").toString(), "x^(y^z)");
  EXPECT_EQ(Expression("(x^y)^z").toString(), "x^(y z)");
  EXPECT_EQ(Expression("(a+b)^2").toString(), "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("(a+b)^3").toString(), "a^3 + 3 a^2 b + 3 a b^2 + b^3");
  EXPECT_EQ(Expression("1*(a+b)^3").toString(), "a^3 + 3 a^2 b + 3 a b^2 + b^3");
  EXPECT_EQ(Expression("(a+b)^4").toString(), "a^4 + 4 a^3 b + 6 a^2 b^2 + 4 a b^3 + b^4");
  EXPECT_EQ(Expression("1*(a+b)*1").toString(), "a + b");
  EXPECT_EQ(Expression("-1*(a+b)*1").toString(), "-a - b");
  EXPECT_EQ(Expression("1*(a+b)*-1").toString(), "-a - b");
  EXPECT_EQ(Expression("-1*(a+b)*-1").toString(), "a + b");
  EXPECT_EQ(Expression("1+(a+b)+1").toString(), "a + b + 2");
  EXPECT_EQ(Expression("-1+(a+b)+1").toString(), "a + b");
  EXPECT_EQ(Expression("1+(a+b)-1").toString(), "a + b");
  EXPECT_EQ(Expression("-1+(a+b)-1").toString(), "a + b - 2");
  EXPECT_EQ(Expression("2*(a+b)*2").toString(), "4 a + 4 b");
  EXPECT_EQ(Expression("-2*(a+b)*2").toString(), "-4 a - 4 b");
  EXPECT_EQ(Expression("2*(a+b)*-2").toString(), "-4 a - 4 b");
  EXPECT_EQ(Expression("-2*(a+b)*-2").toString(), "4 a + 4 b");
  EXPECT_EQ(Expression("2+(a+b)+2").toString(), "a + b + 4");
  EXPECT_EQ(Expression("-2+(a+b)+2").toString(), "a + b");
  EXPECT_EQ(Expression("2+(a+b)-2").toString(), "a + b");
  EXPECT_EQ(Expression("-2+(a+b)-2").toString(), "a + b - 4");
  EXPECT_EQ(Expression("(a+b)+(a+b)-(a+b)").toString(), "a + b");
  EXPECT_EQ(Expression("(a+b)+(a+b)+(-(a+b))").toString(), "a + b");
  EXPECT_EQ(Expression("(a+b)+(a+b)+(-(-(a+b)))").toString(), "3 a + 3 b");
  EXPECT_EQ(Expression("-a^2 + b").toString(), "-a^2 + b");
  EXPECT_EQ(Expression("-a^2 c + b").toString(), "-a^2 c + b");
  EXPECT_EQ(Expression("-a^2 d - a^2 c + b").toString(), "-a^2 c - a^2 d + b");
  EXPECT_EQ(Expression("abc").toString(), "a b c");
  EXPECT_EQ(Expression("d^abc").toString(), "b c d^a");
  EXPECT_EQ(Expression("abc^d").toString(), "a b c^d");
  EXPECT_EQ(Expression("(a+b(a+b(a+b(a+b))))").toString(), "a b^3 + a b^2 + a b + a + b^4");
  EXPECT_EQ(Expression("(ab+(ab+(ab+(ab))))").toString(), "4 a b");
  EXPECT_EQ(Expression("((a+b+(a+c)+(1+v))+((a+c(abc(aaa))+v)c+d))((c)((d+d+d)b)a)").toString(),
            "3 a^5 b^2 c^4 d + 3 a^2 b c^2 d + 6 a^2 b c d + 3 a b^2 c d + 3 a b c^2 d v + 3 a b c^2 d + 3 a b c d^2 + "
            "3 a b c d v + 3 a b c d");
  EXPECT_EQ(Expression("2/(a + 2) + b/(a + 2)").toString(), "(b + 2)/(a + 2)");
  EXPECT_EQ(Expression("c * 2^(a + 2) + b^(a + 2)").toString(), "b^(a + 2) + 2^(a + 2) c");
  EXPECT_EQ(Expression("2^(a + 2) * b^(a + 2)").toString(), "b^(a + 2) 2^(a + 2)");

  EXPECT_EQ(Expression("-9 / (3x+3)").toString(), "-3/(x + 1)");
  EXPECT_EQ(Expression("(4x^2 - 5x - 21) / (x - 3)").toString(), "4 x + 7");
  EXPECT_EQ(Expression("(3x^3 - 5x^2 + 10x - 3) / (3x + 1)").toString(), "x^2 - 2 x + 4 - 7/(3 x + 1)");
  EXPECT_EQ(Expression("(2x^3 - 9x^2 + 15) / (2x - 5)").toString(), "x^2 - 2 x - 5 - 10/(2 x - 5)");
  EXPECT_EQ(Expression("(4x^4 + 1 + 3x^3 + 2x) / (x^2 + x + 2)").toString(),
            "4 x^2 - x - 7 + (11 x + 15)/(x^2 + x + 2)");
  EXPECT_EQ(Expression("(2x^4 - 3x^3 + 4x^2 - 5x + 6) / (x^2 + 2x - 3)").toString(),
            "2 x^2 - 7 x + 24 + (-74 x + 78)/(x^2 + 2 x - 3)");
  EXPECT_EQ(Expression("(4x^5 + 2x^4 - 6x^3 + 3x^2 + x - 2) / (2x^3 + x^2 - 3x + 2)").toString(),
            "2 x^2 + (-x^2 + x - 2)/(2 x^3 + x^2 - 3 x + 2)");
  EXPECT_EQ(Expression("(3x^6 + 5x^5 - 2x^4 + 4x^3 + x^2 + 3x - 5) / (x^4 + 3x^2 - 2)").toString(),
            "3 x^2 + 5 x - 11 + (-11 x^3 + 40 x^2 + 13 x - 27)/(x^4 + 3 x^2 - 2)");
  EXPECT_EQ(Expression("(6x^8 - 7x^6 + 9x^4 - 4x^2 + 8) / (2x^3 - x^2 + 3x - 1)").toString(),
            "3 x^5 + (3 x^4)/2 - (29 x^3)/4 - (35 x^2)/8 + (223 x)/16 + 317/32 + (-1289 x^2 - 505 x + 573)/(64 x^3 - "
            "32 x^2 + 96 x - 32)");
  EXPECT_EQ(Expression("(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)/(25 a^2 + 40 a b + 15 b^2)").toString(),
            "(2 a)/25 + (9 b)/125 + (-2 a b^2 - 2 b^3)/(625 a^2 + 1000 a b + 375 b^2)");
  EXPECT_EQ(Expression("(25 a^2 + 40 a b + 15 b^2)/(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)").toString(),
            "(25 a^2 + 40 a b + 15 b^2)/(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)");
  EXPECT_EQ(Expression("(x^2 + 2x + 1)/(x^3 + 3x^2 + 3x + 1)").toString(), "1/(x + 1)");
  EXPECT_EQ(Expression("5/(a+b) + 5/(2a+b) + 5/(a+b)").toString(),
            "(25 a^2 + 40 a b + 15 b^2)/(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)");
  EXPECT_EQ(Expression("(x+y)/(a+b) + 5/(2a+b) + (x+2y)/(a+b)").toString(),
            "(4 a x + 6 a y + 5 a + 2 b x + 3 b y + 5 b)/(2 a^2 + 3 a b + b^2)");
  EXPECT_EQ(Expression("(a/b)(c/d)").toString(), "(a c)/(b d)");
  EXPECT_EQ(Expression("(ab/2)(ad/3)").toString(), "(a^2 b d)/6");
  EXPECT_EQ(Expression("(-a)(-b)").toString(), "a b");
  EXPECT_EQ(Expression("(a)(-b)").toString(), "-a b");
  EXPECT_EQ(Expression("(-a)(b)").toString(), "-a b");
  EXPECT_EQ(Expression("(5/3 b)/a").toString(), "(5 b)/(3 a)");
  EXPECT_EQ(Expression("(5/3 + b)/(2/5 + a)").toString(), "(15 b + 25)/(15 a + 6)");
  EXPECT_EQ(Expression("(a b)/(a b)").toString(), "1");
  EXPECT_EQ(Expression("(a b)/1").toString(), "a b");
  EXPECT_EQ(Expression("(a b)/-1").toString(), "-a b");
  EXPECT_EQ(Expression("(a b)/-2").toString(), "-(a b)/2");
  EXPECT_EQ(Expression("(a b)/(-a - b)").toString(), "-b + (b^2)/(a + b)");
  EXPECT_EQ(Expression("(x^5)/(x - y)").toString(), "x^4 + x^3 y + x^2 y^2 + x y^3 + y^4 + (y^5)/(x - y)");
  EXPECT_EQ(Expression("(3 x + 5/9)/(2y - 9/x + 3/2 x + 1/2 + 2 y / x)").toString(),
            "2 + (-72 x y - 8 x - 72 y + 324)/(27 x^2 + 36 x y + 9 x + 36 y - 162)");
  EXPECT_EQ(Expression("(a/x + b/(y+3/r)/4)/(3+t/5)").toString(),
            "(20 a r y + 60 a + 5 b r x)/(4 r t x y + 60 r x y + 12 t x + 180 x)");
  EXPECT_EQ(Expression("(x/a - (b+5)/(y-8/(12 y))/4)/(8-a/5)").toString(),
            "(-a b - 5 a + 4 x y + (-8 x)/(3 y))/(-(4 a^2 y)/5 + 32 a y + (8 a^2)/(15 y) + (-64 a)/(3 y))");
  EXPECT_EQ(Expression("(a + b + c^2) / ((a + b + c^3) / (5/2 * (a + b) / (3/b + c/2)))").toString(),
            "5 c + (5 a^2 b + 10 a b^2 - 30 a c + 5 b^3 - 5 b c^5 - 30 b c - 30 c^4)/(a b c + 6 a + b^2 c + b c^4 + 6 "
            "b + 6 c^3)");
  EXPECT_EQ(Expression("((2xy)/(x^2 - y^2) + (x - y)/(2x + 2y)) * (2x)/(x + y) + y/(y - x)").toString(), "1");
  EXPECT_EQ(Expression("y/(x - y) - (x ^3 - xy ^2)/(x ^2 + y ^2) * (x/((x - y) ^2) - y/(x ^2 - y ^2))").toString(),
            "-1");
  EXPECT_EQ(Expression("(a+3)/(b+2)").toString(), "(a + 3)/(b + 2)");
  EXPECT_EQ(Expression("b/a*(a+3)/(b+2)").toString(), "1 + (-2 a + 3 b)/(a b + 2 a)");
  EXPECT_EQ(Expression("(5+b)/a*(a+3)/(b+2)").toString(), "1 + (3 a + 3 b + 15)/(a b + 2 a)");
  EXPECT_EQ(Expression("(a+b)*(a+b)/(a+b)").toString(), "a + b");
  EXPECT_EQ(Expression("(a+b)*(a+b)*(1/(a+b))").toString(), "a + b");
  EXPECT_EQ(Expression("(x^2+2x+1)/(x+1)").toString(), "x + 1");

  EXPECT_EQ(Expression("(x/y)^2").toString(), "(x^2)/(y^2)");
  EXPECT_EQ(Expression("(x/y)^(1/2)").toString(), "sqrt(x)/sqrt(y)");
  EXPECT_EQ(Expression("(x/y)^(1/3)").toString(), "root(x, 3)/root(y, 3)");
  EXPECT_EQ(Expression("(x/y)^(-1/2)").toString(), "sqrt(y)/sqrt(x)");
  EXPECT_EQ(Expression("(x/y)^(-1/3)").toString(), "root(y, 3)/root(x, 3)");
  EXPECT_EQ(Expression("(x/y)^x").toString(), "(x^x)/(y^x)");
  EXPECT_EQ(Expression("(x/y)^(1/x)").toString(), "root(x, x)/root(y, x)");

  EXPECT_EQ(Expression("sqrt(x) + x").toString(), "x + sqrt(x)");
  EXPECT_EQ(Expression("sqrt(x) - x").toString(), "-x + sqrt(x)");
  EXPECT_EQ(Expression("x/(sqrt(x) - x)").toString(), "-1 - (sqrt(x)/(x - sqrt(x)))");
  EXPECT_EQ(Expression("x/(2 sqrt(x) - x)").toString(), "-1 + (-2 sqrt(x))/(x - 2 sqrt(x))");
  EXPECT_EQ(Expression("(x-1)/(sqrt(x) - x)").toString(), "-1 - 1/sqrt(x)");
  EXPECT_EQ(Expression("(x-1)/(2 sqrt(x) - x)").toString(), "-1 + (-2 sqrt(x) + 1)/(x - 2 sqrt(x))");
  EXPECT_EQ(Expression("(x-1)/(sqrt(x)/2 - x)").toString(), "-1 + (sqrt(x) - 2)/(-2 x + sqrt(x))");
  EXPECT_EQ(Expression("(x-1)/(root(x, 3) - x)").toString(), "-1 + (-root(x, 3) + 1)/(x - root(x, 3))");
  EXPECT_EQ(Expression("(x-1)/(2 root(x, 3) - x)").toString(), "-1 + (-2 root(x, 3) + 1)/(x - 2 root(x, 3))");
  EXPECT_EQ(Expression("(x-1)/(root(x, 3)/2 - x)").toString(), "-1 + (root(x, 3) - 2)/(-2 x + root(x, 3))");
  EXPECT_EQ(Expression("(x-1)/(x^(4/3) - x)").toString(), "(x - 1)/(x^(4/3) - x)");
  EXPECT_EQ(Expression("(x-1)/(2 x^(4/3) - x)").toString(), "(x - 1)/(2 x^(4/3) - x)");

  // TODO! implement this
  // EXPECT_EQ(Expression("sqrt(x^2)").toString(), "abs(x)");
  // EXPECT_EQ(Expression("(x^10)^(1/10))").toString(), "abs(x)");
  // EXPECT_EQ(Expression("(x^3)^(1/3)").toString(), "x");
  // EXPECT_EQ(Expression("sqrt(x)^2").toString(), "x");
  // EXPECT_EQ(Expression("sqrt(x) * sqrt(x)").toString(), "x");
  // EXPECT_EQ(Expression("abs(x)^3").toString(), "abs(x^3)");
  // EXPECT_EQ(Expression("abs(x^3)").toString(), "abs(x^3)");

  EXPECT_EQ(Expression("(a+b+1-1)^1000/(a+b+1-1)^998").toString(), "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("(a+b)^1000/(a+b)^998").toString(), "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("sin(asin(a+b+1-1))^1000/(a+b+1-1)^998").toString(), "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("a(10^100)/10^99").toString(), "10 a");
  EXPECT_EQ(Expression("(10+2+3-5)^1000000000a/(9+1)^999999999").toString(), "10 a");
  EXPECT_EQ(Expression("10^(10^100/10^96)a/10^9999").toString(), "10 a");
  EXPECT_EQ(Expression("10^(10^100/10^90)a/10^9999999999").toString(), "10 a");
  EXPECT_EQ(Expression("log(1000!,1000!)").toString(), "1");
  EXPECT_EQ(Expression("log(100000000000!,100000000000!)").toString(), "1");

  EXPECT_EQ(Expression("-sin(x)").toString(), "-sin(x)");
  EXPECT_EQ(Expression("-sin(x) + sin(2)").toString(), "-sin(x) + sin(2)");
  EXPECT_EQ(Expression("-3sin(E)").toString(), "-3 sin(E)");
  EXPECT_EQ(Expression("1-(sin(x)+1)").toString(), "-sin(x)");
  EXPECT_EQ(Expression("1/(sin(x)+1)").toString(), "1/(sin(x) + 1)");
  EXPECT_EQ(Expression("(x+1)^3").toString(), "x^3 + 3 x^2 + 3 x + 1");
  EXPECT_EQ(Expression("(x+1)^(-3)").toString(), "1/(x^3 + 3 x^2 + 3 x + 1)");
  EXPECT_EQ(Expression("(sin(x)+1)^3").toString(), "sin(x)^3 + 3 sin(x)^2 + 3 sin(x) + 1");
  EXPECT_EQ(Expression("(sin(x)+1)^(-3)").toString(), "1/(sin(x)^3 + 3 sin(x)^2 + 3 sin(x) + 1)");
  EXPECT_EQ(Expression("(sin(x)+1)^(-4)").toString(), "1/(sin(x)^4 + 4 sin(x)^3 + 6 sin(x)^2 + 4 sin(x) + 1)");
  EXPECT_EQ(Expression("(x)sin(a)").toString(), "sin(a) x");
  EXPECT_EQ(Expression("tan(4 a^3 b) + cot(4 a b^3) + b^4 + sin(a^4) + cos(6 a^2 b^2)").toString(),
            "b^4 + sin(a^4) + tan(4 a^3 b) + cos(6 a^2 b^2) + cot(4 a b^3)");
  EXPECT_EQ(Expression("tan(4 a^3 b) + cot(sin(4 a b^3)) + b^4 + asin(sin(a^4)) + cos(6 a^2 b^2)").toString(),
            "b^4 + asin(sin(a^4)) + tan(4 a^3 b) + cos(6 a^2 b^2) + cot(sin(4 a b^3))");
  EXPECT_EQ(Expression("tan(4 a_1^3 b) + cot(sin(4 a_1 b^3)) + b^4 + asin(sin(a_1^4)) + cos(6 a_1^2 b^2)").toString(),
            "b^4 + asin(sin(a_1^4)) + tan(4 a_1^3 b) + cos(6 a_1^2 b^2) + cot(sin(4 a_1 b^3))");
  EXPECT_EQ(Expression("a!!!!!!!!!!").toString(), "a!!!!!!!!!!");
  EXPECT_EQ(Expression("a% * a!!! * a! * a!!").toString(), "(a a! a!! a!!!)/100");
  EXPECT_EQ(Expression("a! sin(a)").toString(), "a! sin(a)");
  EXPECT_EQ(Expression("sin(a) a!").toString(), "a! sin(a)");
  EXPECT_EQ(Expression("sin(a) a").toString(), "a sin(a)");
  EXPECT_EQ(Expression("a sin(a)").toString(), "a sin(a)");
  EXPECT_EQ(Expression("cos(b) sin(a)").toString(), "sin(a) cos(b)");
  EXPECT_EQ(Expression("cos(b) log(b, a)").toString(), "log(b, a) cos(b)");
  EXPECT_EQ(Expression("cos(a) log(b, c)").toString(), "log(b, c) cos(a)");
  EXPECT_EQ(Expression("cos(b^2) log(b, c)").toString(), "log(b, c) cos(b^2)");
  EXPECT_EQ(Expression("(x + y^3)^2 * sin(x)/ln(2)/x^2 - (2 sin(x) y^3)/(x ln(2))").toString(),
            "sin(x)/ln(2) + (y^6 sin(x))/(x^2 ln(2))");

  EXPECT_EQ(Expression("a=a").toString(), "True");
  EXPECT_EQ(Expression("a+a=2*a").toString(), "True");
  EXPECT_EQ(Expression("a=b").toString(), "a - b = 0");
  EXPECT_EQ(Expression("a!=a").toString(), "False");
  EXPECT_EQ(Expression("a+a!=2*a").toString(), "False");
  EXPECT_EQ(Expression("a!=b").toString(), "a - b != 0");
  EXPECT_EQ(Expression("x<6").toString(), "x - 6 < 0");
  EXPECT_EQ(Expression("x<=6").toString(), "x - 6 <= 0");
  EXPECT_EQ(Expression("x>6").toString(), "x - 6 > 0");
  EXPECT_EQ(Expression("x>=6").toString(), "x - 6 >= 0");
  EXPECT_EQ(Expression("(5+5)=(2*5)").toString(), "True");
  EXPECT_EQ(Expression("((((5+5)=(2*5))))").toString(), "True");
  EXPECT_EQ(Expression("((1*1))(5+5)=((2*5)/(1/1))").toString(), "True");
  EXPECT_EQ(Expression("-x - 10 = 0").toString(), "x + 10 = 0");
  EXPECT_EQ(Expression("2x = 0").toString(), "x = 0");
  EXPECT_EQ(Expression("2x - 10 = 0").toString(), "x - 5 = 0");
  EXPECT_EQ(Expression("-a > 0").toString(), "a < 0");
  EXPECT_EQ(Expression("-2a + 5 > 6").toString(), "a + 1/2 < 0");
  EXPECT_EQ(Expression("-2a+5>6").toString(), "a + 1/2 < 0");
  EXPECT_EQ(Expression("-6x^2 + 4x - 20 = 15x - 9").toString(), "x^2 + (11 x)/6 + 11/6 = 0");
  EXPECT_EQ(Expression("2 a^5 b - 4 a b^5  = 0").toString(), "a^5 b - 2 a b^5 = 0");
  EXPECT_EQ(Expression("-2 a^5 b + 4 a b^5  = 0").toString(), "a^5 b - 2 a b^5 = 0");

  EXPECT_EQ(Expression("sin(E)=sin(E)").toString(), "True");
  EXPECT_EQ(Expression("sin(E)>sin(E)").toString(), "False");
  EXPECT_EQ(Expression("sin(E)>=sin(E)").toString(), "True");
  EXPECT_EQ(Expression("sin(E)<sin(E)").toString(), "False");
  EXPECT_EQ(Expression("sin(E)<=sin(E)").toString(), "True");
  EXPECT_EQ(Expression("log(E,5)=ln(5)").toString(), "True");
  EXPECT_EQ(Expression("log(E,5)<ln(5)").toString(), "False");
  EXPECT_EQ(Expression("log(E,5)>ln(5)").toString(), "False");
  EXPECT_EQ(Expression("log(E,5)<=ln(5)").toString(), "True");
  EXPECT_EQ(Expression("log(E,5)>=ln(5)").toString(), "True");
  EXPECT_EQ(Expression("log(1deg, 1deg^1deg) = 1deg").toString(), "True");
  EXPECT_EQ(Expression("E^Pi > Pi^E").toString(), "-Pi^E + E^Pi > 0"); // TODO: True
  EXPECT_EQ(Expression("Pi^E < E^Pi").toString(), "Pi^E - E^Pi < 0");  // TODO: True

  EXPECT_EQ(Expression("derivative(a, a)").toString(), "1");
  EXPECT_EQ(Expression("derivative(a+a, a)").toString(), "derivative(2 a, a)");
  EXPECT_EQ(Expression("derivative(a, a) + derivative(b, b)").toString(), "2");
  // TODO: derivative
  // EXPECT_EQ(Expression("derivative(5, a^2)").toString(), "0");
  // EXPECT_EQ(Expression("derivative(a, a^2)").toString(), "derivative(a, a^2)");

  EXPECT_EQ(Expression("integral(a, a)").toString(), "(a^2)/2");
  EXPECT_EQ(Expression("integral(a+a, a)").toString(), "integral(2 a, a)");
  EXPECT_EQ(Expression("integral(a, a) + integral(b, b)").toString(), "(a^2)/2 + (b^2)/2");
  // TODO: integral
  // EXPECT_EQ(Expression("integral(5, a^2)").toString(), "???");
  // EXPECT_EQ(Expression("integral(a, a^2)").toString(), "???");

  EXPECT_EQ(Expression("~True").toString(), "False");
  EXPECT_EQ(Expression("~False").toString(), "True");
  EXPECT_EQ(Expression("True&False").toString(), "False");
  EXPECT_EQ(Expression("~~~True&~~~~False|~~~~~~False|False").toString(), "False");
  EXPECT_EQ(Expression("True|False").toString(), "True");
  EXPECT_EQ(Expression("True&False|True&False").toString(), "False");
  EXPECT_EQ(Expression("False&True|True&False").toString(), "False");
  EXPECT_EQ(Expression("False&True|True&True|False").toString(), "True");
  EXPECT_EQ(Expression("False|~False&True").toString(), "True");
  EXPECT_EQ(Expression("(False|False&~True)|(True&~(False|True))").toString(), "False");
  EXPECT_EQ(Expression("True !<-> True").toString(), "False");
  EXPECT_EQ(Expression("(False -> False & ~True) !<-> (True <-> ~(False|True))").toString(), "True");
  EXPECT_EQ(Expression("False <-> ~False & True").toString(), "False");
  EXPECT_EQ(Expression("False <-> True -> False").toString(), "True");

  EXPECT_EQ(Expression("~(1=1)").toString(), "False");
  EXPECT_EQ(Expression("~(1=2)").toString(), "True");
  EXPECT_EQ(Expression("(1=1)&(1=2)").toString(), "False");
  EXPECT_EQ(Expression("(1=1)|(1=2)").toString(), "True");
  EXPECT_EQ(Expression("(1=2)|~(1=2)&(1=1)").toString(), "True");
  EXPECT_EQ(Expression("((1=2)|(1=2)&~(1=1))|((1=1)&~((1=2)|(1=1)))").toString(), "False");
  EXPECT_EQ(Expression("((1=2) -> (1=2) & ~(1=1)) !<-> ((1=1) <-> ~((1=2) | (1=1)))").toString(), "True");
  EXPECT_EQ(Expression("False|1=1").toString(), "True");
  EXPECT_EQ(Expression("1=1|False").toString(), "True");
  EXPECT_EQ(Expression("a>b|a").toString(), "a - b > 0 | a");

  EXPECT_EQ(Expression("~(x = 1)").toString(), "x - 1 != 0");
  EXPECT_EQ(Expression("~(x != 1)").toString(), "x - 1 = 0");
  EXPECT_EQ(Expression("~(x > 1)").toString(), "x - 1 <= 0");
  EXPECT_EQ(Expression("~(x < 1)").toString(), "x - 1 >= 0");
  EXPECT_EQ(Expression("~(x >= 1)").toString(), "x - 1 < 0");
  EXPECT_EQ(Expression("~(x <= 1)").toString(), "x - 1 > 0");
  EXPECT_EQ(Expression("~(x <= 1 | y >= 1)").toString(), "x - 1 > 0 & y - 1 < 0");

  EXPECT_EQ(Expression("~a").toString(), "~a");
  EXPECT_EQ(Expression("~~a").toString(), "a");
  EXPECT_EQ(Expression("~~~a").toString(), "~a");
  EXPECT_EQ(Expression("~~~~~~~~~~a").toString(), "a");
  EXPECT_EQ(Expression("~~~~~~~~~~~a").toString(), "~a");

  EXPECT_EQ(Expression("a & b").toString(), "a & b");
  EXPECT_EQ(Expression("a | b").toString(), "a | b");
  EXPECT_EQ(Expression("a -> b").toString(), "~a | b");
  EXPECT_EQ(Expression("a <-> b").toString(), "(a & b) | (~a & ~b)");
  EXPECT_EQ(Expression("a !<-> b").toString(), "(a & ~b) | (~a & b)");

  EXPECT_EQ(Expression("a & a").toString(), "a");
  EXPECT_EQ(Expression("a | a").toString(), "a");
  EXPECT_EQ(Expression("a -> a").toString(), "True");
  EXPECT_EQ(Expression("a <-> a").toString(), "True");
  EXPECT_EQ(Expression("a !<-> a").toString(), "False");

  EXPECT_EQ(Expression("a & ~a").toString(), "False");
  EXPECT_EQ(Expression("a | ~a").toString(), "True");
  EXPECT_EQ(Expression("a -> ~a").toString(), "~a");
  EXPECT_EQ(Expression("a <-> ~a").toString(), "False");
  EXPECT_EQ(Expression("a !<-> ~a").toString(), "True");

  EXPECT_EQ(Expression("~a & a").toString(), "False");
  EXPECT_EQ(Expression("~a | a").toString(), "True");
  EXPECT_EQ(Expression("~a -> a").toString(), "a");
  EXPECT_EQ(Expression("~a <-> a").toString(), "False");
  EXPECT_EQ(Expression("~a !<-> a").toString(), "True");

  EXPECT_EQ(Expression("~a & ~a").toString(), "~a");
  EXPECT_EQ(Expression("~a | ~a").toString(), "~a");
  EXPECT_EQ(Expression("~a -> ~a").toString(), "True");
  EXPECT_EQ(Expression("~a <-> ~a").toString(), "True");
  EXPECT_EQ(Expression("~a !<-> ~a").toString(), "False");

  EXPECT_EQ(Expression("a & False").toString(), "False");
  EXPECT_EQ(Expression("a | False").toString(), "a");
  EXPECT_EQ(Expression("a -> False").toString(), "~a");
  EXPECT_EQ(Expression("a <-> False").toString(), "~a");
  EXPECT_EQ(Expression("a !<-> False").toString(), "a");

  EXPECT_EQ(Expression("a & True").toString(), "a");
  EXPECT_EQ(Expression("a | True").toString(), "True");
  EXPECT_EQ(Expression("a -> True").toString(), "True");
  EXPECT_EQ(Expression("a <-> True").toString(), "a");
  EXPECT_EQ(Expression("a !<-> True").toString(), "~a");

  EXPECT_EQ(Expression("a<->(True)<->(False)").toString(), "~a");
  EXPECT_EQ(Expression("a<->(True)!<->(False)").toString(), "a");
  EXPECT_EQ(Expression("True & b & False & c").toString(), "False");
  EXPECT_EQ(Expression("True | b | False | c").toString(), "True");
  EXPECT_EQ(Expression("True | a | b | False").toString(), "True");
  EXPECT_EQ(Expression("a<->a<->a<->a<->a<->a").toString(), "True");
  EXPECT_EQ(Expression("a<->a<->a<->a<->a<->a<->a").toString(), "a");
  EXPECT_EQ(Expression("a&b->b&c").toString(), "~a | (b & c) | ~b");
  EXPECT_EQ(Expression("a&b&c").toString(), "a & b & c");
  EXPECT_EQ(Expression("a&(b&c)").toString(), "a & b & c");
  EXPECT_EQ(Expression("a & ~b & c").toString(), "a & ~b & c");
  EXPECT_EQ(Expression("a | (~b & c)").toString(), "a | (~b & c)");
  EXPECT_EQ(Expression("(a | ~b) & c").toString(), "(a & c) | (~b & c)");
  EXPECT_EQ(Expression("~(a & b)").toString(), "~a | ~b");
  EXPECT_EQ(Expression("~(a | b)").toString(), "~a & ~b");
  EXPECT_EQ(Expression("~(a & b & c)").toString(), "~a | ~b | ~c");
  EXPECT_EQ(Expression("~(a | b | c)").toString(), "~a & ~b & ~c");
  EXPECT_EQ(Expression("~(~a & ~a)").toString(), "a");
  EXPECT_EQ(Expression("b&c&d | a&c&d | a&b&c").toString(), "(a & b & c) | (a & c & d) | (b & c & d)");
  EXPECT_EQ(Expression("a | (a & b)").toString(), "a");
  EXPECT_EQ(Expression("(a & b & c) | (a & b)").toString(), "a & b");
  EXPECT_EQ(Expression("a & (a | b)").toString(), "a");
  EXPECT_EQ(Expression("(a | b | c) & (a | b)").toString(), "a | b");
  EXPECT_EQ(Expression("(a & b & c) | (a & c)").toString(), "a & c");
  EXPECT_EQ(Expression("(a & ~b) | (a & b)").toString(), "a");
  EXPECT_EQ(Expression("(a | b | c) & (a | b)").toString(), "a | b");
  EXPECT_EQ(Expression("~(a & b) | ~(~a & c)").toString(), "True");
  EXPECT_EQ(Expression("~(a | b) & ~(~a | c)").toString(), "False");
  EXPECT_EQ(Expression("(x & ~y & z) | (y & z)").toString(), "(x & ~y & z) | (y & z)");
  EXPECT_EQ(Expression("(x | ~y | (x | ~y | z) & (y | z)) & (y | (x & ~y & z) | (y & z))").toString(),
            "(x & ~y & z) | (x & y) | (y & z)");
  EXPECT_EQ(Expression("~a & b | ~c -> a <-> b !<-> c").toString(),
            "(a & b & ~c) | (~a & ~b & ~c) | (~a & c) | (~b & c)");
  EXPECT_EQ(Expression("~~~a & ~~b | ~~~c -> ~~a <-> ~~b !<-> ~~c").toString(),
            "(a & b & ~c) | (~a & ~b & ~c) | (~a & c) | (~b & c)");
  EXPECT_EQ(Expression("((a | b) & (a -> c)) <-> (~a -> b)").toString(), "(a & c) | ~a | (b & c)");

  EXPECT_EQ(Expression("x=1&a").toString(), "a & x - 1 = 0");
  EXPECT_EQ(Expression("True & a = b").toString(), "a - b = 0");

  EXPECT_EQ(Expression("x_1").toString(), "x_1");
  EXPECT_EQ(Expression("x+x_1").toString(), "x + x_1");
  EXPECT_EQ(Expression("x*x_1").toString(), "x x_1");
  EXPECT_EQ(Expression("x_2^2").toString(), "x_2^2");
  EXPECT_EQ(Expression("sin(x_1)").toString(), "sin(x_1)");

  EXPECT_EQ(Expression("min(1)").toString(), "1");
  EXPECT_EQ(Expression("min(1,2)").toString(), "1");
  EXPECT_EQ(Expression("min(1,2,3)").toString(), "1");
  EXPECT_EQ(Expression("min(1, 2, 3, 4)").toString(), "1");
  EXPECT_EQ(Expression("min(-1, -2, -3, -4)").toString(), "-4");
  EXPECT_EQ(Expression("min(x)").toString(), "x");
  EXPECT_EQ(Expression("min(1,x)").toString(), "min(x, 1)");
  EXPECT_EQ(Expression("min(1,2,x)").toString(), "min(x, 1)");
  EXPECT_EQ(Expression("min(1, 2, x, 4)").toString(), "min(x, 1)");
  EXPECT_EQ(Expression("min(-1, x, y, -4)").toString(), "min(x, y, -4)");
  EXPECT_EQ(Expression("min(E, x, y, z)").toString(), "min(x, y, z, E)");

  EXPECT_EQ(Expression("max(1)").toString(), "1");
  EXPECT_EQ(Expression("max(1,2)").toString(), "2");
  EXPECT_EQ(Expression("max(1,2,3)").toString(), "3");
  EXPECT_EQ(Expression("max(1, 2, 3, 4)").toString(), "4");
  EXPECT_EQ(Expression("max(-1, -2, -3, -4)").toString(), "-1");
  EXPECT_EQ(Expression("max(x)").toString(), "x");
  EXPECT_EQ(Expression("max(1,x)").toString(), "max(x, 1)");
  EXPECT_EQ(Expression("max(1,2,x)").toString(), "max(x, 2)");
  EXPECT_EQ(Expression("max(1, 2, x, 4)").toString(), "max(x, 4)");
  EXPECT_EQ(Expression("max(-1, x, y, -4)").toString(), "max(x, y, -1)");
  EXPECT_EQ(Expression("max(E, x, y, z)").toString(), "max(x, y, z, E)");

  EXPECT_EQ(Expression("ln(x) + ln(y)").toString(), "ln(x y)");
  EXPECT_EQ(Expression("ln(x) - ln(y)").toString(), "ln(x/y)");
  EXPECT_EQ(Expression("-ln(x) + ln(y)").toString(), "ln(y/x)");
  EXPECT_EQ(Expression("-ln(x) - ln(y)").toString(), "ln(1/(x y))");
  EXPECT_EQ(Expression("lb(x)/y").toString(), "log(2, x)/y");
  EXPECT_EQ(Expression("ln((E)/(20000.1EE)) + ln(20000.1E)").toString(), "0");
  EXPECT_EQ(Expression("ln((10 E)^2) - ln(10 E 10 E)").toString(), "0");
  EXPECT_EQ(Expression("ln((10 E)^2) - 2 ln(10 E)").toString(), "0");
  EXPECT_EQ(Expression("3 ln((10 E)^2) - 2 ln(10 E)").toString(), "4 ln(10 E)");
  EXPECT_EQ(Expression("ln((10 E)^(2ab)) - 2 a ln(10 E) b").toString(), "0");
  EXPECT_EQ(Expression("ln((10 E)^(2 ln(2))) - 2 ln(2) ln(10 E)").toString(), "0");
  EXPECT_EQ(Expression("log(2.3,(E)/(20000.1EE)) + log(2.3,20000.1E)").toString(), "0");
  EXPECT_EQ(Expression("log(2, 3) + log(3, 4)").toString(), "log(3, 4) + log(2, 3)");
  EXPECT_EQ(Expression("x log(2, 3) + log(2, 5)").toString(), "log(2, 5 3^x)");
  EXPECT_EQ(Expression("x log(2, 3) + log(2, 5a)").toString(), "log(2, 5 a 3^x)");
  EXPECT_EQ(Expression("log(2, 3) + 3log(3, 4)").toString(), "3 log(3, 4) + log(2, 3)");
  EXPECT_EQ(Expression("3log(2x, 3) + log(3, 4)").toString(), "3 log(2 x, 3) + log(3, 4)");
  EXPECT_EQ(Expression("3log(2x, 3) + 4log(3, 4)").toString(), "3 log(2 x, 3) + 4 log(3, 4)");
  EXPECT_EQ(Expression("3log(2x, 3) + 5log(2x, 4)").toString(), "log(2 x, 27648)");

  EXPECT_EQ(Expression("sin(asin(x))").toString(), "x");
  EXPECT_EQ(Expression("cos(acos(x))").toString(), "x");
  EXPECT_EQ(Expression("tan(atan(x))").toString(), "x");
  EXPECT_EQ(Expression("cot(acot(x))").toString(), "x");
  EXPECT_EQ(Expression("sinh(asinh(x))").toString(), "x");
  EXPECT_EQ(Expression("cosh(acosh(x))").toString(), "x");
  EXPECT_EQ(Expression("tanh(atanh(x))").toString(), "x");
  EXPECT_EQ(Expression("coth(acoth(x))").toString(), "x");
  EXPECT_EQ(Expression("asin(sin(x))").toString(), "asin(sin(x))");
  EXPECT_EQ(Expression("acos(cos(x))").toString(), "acos(cos(x))");
  EXPECT_EQ(Expression("atan(tan(x))").toString(), "atan(tan(x))");
  EXPECT_EQ(Expression("acot(cot(x))").toString(), "acot(cot(x))");
  EXPECT_EQ(Expression("asinh(sinh(x))").toString(), "asinh(sinh(x))");
  EXPECT_EQ(Expression("acosh(cosh(x))").toString(), "acosh(cosh(x))");
  EXPECT_EQ(Expression("atanh(tanh(x))").toString(), "atanh(tanh(x))");
  EXPECT_EQ(Expression("acoth(coth(x))").toString(), "acoth(coth(x))");

  // EXPECT_EQ(Expression("sin(x)^2 + cos(x)^2").toString(), "1"); // TODO: implement
  // EXPECT_EQ(Expression("tan(x)*cot(x)").toString(), "1"); // TODO: implement
  // EXPECT_EQ(Expression("tanh(x)*coth(x)").toString(), "1"); // TODO: implement

  EXPECT_EQ(Expression("Inf").toString(), "Inf");
  EXPECT_EQ(Expression("-Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("ComplexInf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("-ComplexInf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("1/0").toString(), "ComplexInf");
  EXPECT_EQ(Expression("a/0").toString(), "ComplexInf");
  EXPECT_EQ(Expression("1/Inf").toString(), "0");
  EXPECT_EQ(Expression("1/-Inf").toString(), "0");
  EXPECT_EQ(Expression("a/Inf").toString(), "0");
  EXPECT_EQ(Expression("a/-Inf").toString(), "0");
  EXPECT_EQ(Expression("1/ComplexInf").toString(), "0");
  EXPECT_EQ(Expression("a/ComplexInf").toString(), "0");
  EXPECT_EQ(Expression("Inf + Inf").toString(), "Inf");
  EXPECT_EQ(Expression("-Inf - Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("10 + Inf").toString(), "Inf");
  EXPECT_EQ(Expression("-10 + Inf").toString(), "Inf");
  EXPECT_EQ(Expression("10 - Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("-10 - Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("a + Inf").toString(), "Inf");
  EXPECT_EQ(Expression("-a - Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("10 * Inf").toString(), "Inf");
  EXPECT_EQ(Expression("-10 * Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("-2/3 * Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("a * Inf").toString(), "Inf a");
  EXPECT_EQ(Expression("Inf * Inf").toString(), "Inf");
  EXPECT_EQ(Expression("Inf * -Inf").toString(), "-Inf");
  EXPECT_EQ(Expression("-Inf * -Inf").toString(), "Inf");
  EXPECT_EQ(Expression("ComplexInf*ComplexInf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf*Inf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("ComplexInf*-Inf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("Inf^2").toString(), "Inf");
  EXPECT_EQ(Expression("Inf^(2/3)").toString(), "Inf");
  EXPECT_EQ(Expression("(-Inf)^2").toString(), "Inf");
  EXPECT_EQ(Expression("(-Inf)^3").toString(), "-Inf");
  // EXPECT_EQ(Expression("(-Inf)^(2/3)").toString(), "-Inf"); // TODO! complex numbers
  EXPECT_EQ(Expression("0^Inf").toString(), "0");
  EXPECT_EQ(Expression("0^-Inf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("2^Inf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("2^-Inf").toString(), "0");
  EXPECT_EQ(Expression("2^ComplexInf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("0.2^Inf").toString(), "0");
  EXPECT_EQ(Expression("0.2^-Inf").toString(), "ComplexInf");
  EXPECT_EQ(Expression("0.2^ComplexInf").toString(), "0");
  EXPECT_EQ(Expression("sqrt(2) * Inf").toString(), "Inf sqrt(2)");   // TODO! Inf
  EXPECT_EQ(Expression("-sqrt(2) * Inf").toString(), "-Inf sqrt(2)"); // TODO! -Inf
  EXPECT_EQ(Expression("sin(Inf)").toString(), "sin(Inf)");           // TODO: [-1, 1]
  EXPECT_EQ(Expression("x = Inf").toString(), "False");
  EXPECT_EQ(Expression("x = -Inf").toString(), "False");
  EXPECT_EQ(Expression("Inf = Inf").toString(), "True");
  EXPECT_EQ(Expression("Inf = -Inf").toString(), "False");

  EXPECT_EQ(Expression("0*Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("0*-Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("0*ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf - Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf - ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf + ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf + Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf - Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("0/0").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf/Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("0/Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf/0").toString(), "Undefined");
  EXPECT_EQ(Expression("-Inf/-Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("0/-Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("-Inf/0").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf/-Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("-Inf/Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf/ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("0/ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf/0").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf/Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf/-Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf/ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("-Inf/ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("-Inf + Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf - Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("0^0").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf^0").toString(), "Undefined");
  EXPECT_EQ(Expression("1^Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("1^-Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("1^ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf - Inf = 0").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf - Inf = 0 | a").toString(), "Undefined");
  EXPECT_EQ(Expression("0/0 = 0/0").toString(), "Undefined");
  EXPECT_EQ(Expression("sin(0/0)").toString(), "Undefined");
  EXPECT_EQ(Expression("1 + 0^0").toString(), "Undefined");
  EXPECT_EQ(Expression("1 + sin(asin(0^0)) + x").toString(), "Undefined");
  EXPECT_EQ(Expression("1 + (2^2 - 4)^0").toString(), "Undefined");
  EXPECT_EQ(Expression("0^((2^2 - 4)^0)").toString(), "Undefined");
  EXPECT_EQ(Expression("-((2^2 - 4)^0)").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf = ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf = Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("ComplexInf = -Inf").toString(), "Undefined");
  EXPECT_EQ(Expression("Inf = ComplexInf").toString(), "Undefined");
  EXPECT_EQ(Expression("-Inf = ComplexInf").toString(), "Undefined");

  EXPECT_EQ(Expression("Undefined").toString(), "Undefined");
  EXPECT_EQ(Expression("-Undefined").toString(), "Undefined");
  EXPECT_EQ(Expression("Undefined + 10").toString(), "Undefined");
  EXPECT_EQ(Expression("Undefined - 10").toString(), "Undefined");
  EXPECT_EQ(Expression("0/Undefined").toString(), "Undefined");
  EXPECT_EQ(Expression("1/Undefined").toString(), "Undefined");
  EXPECT_EQ(Expression("Undefined^1").toString(), "Undefined");
  EXPECT_EQ(Expression("Undefined^0").toString(), "Undefined");
  EXPECT_EQ(Expression("sin(Undefined)").toString(), "Undefined");
  EXPECT_EQ(Expression("Undefined = Undefined").toString(), "Undefined");
}

TEST(ExpressionTests, stringConstructorLargeTest) {
  EXPECT_EQ(Expression("10^-500").toString(),
            "1/"
            "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
            "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
            "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
            "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
            "00000000000000000000000000000000000000000000000000000000000000000000000000000");

  EXPECT_EQ(
      Expression("-----------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------a")
          .toString(),
      "a");

  EXPECT_EQ(
      Expression("-----------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "-----------------------------------------------------------------------------------------------------"
                 "------------------------------------------------------------------------a")
          .toString(),
      "-a");

  EXPECT_EQ(
      Expression("a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+"
                 "a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+"
                 "a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+"
                 "a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+"
                 "a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+"
                 "a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a")
          .toString(),
      "266 a");

  EXPECT_EQ(
      Expression("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~a")
          .toString(),
      "a");

  EXPECT_EQ(
      Expression("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                 "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~a")
          .toString(),
      "~a");

  EXPECT_EQ(
      Expression("(x+y)^20").toString(),
      "x^20 + 20 x^19 y + 190 x^18 y^2 + 1140 x^17 y^3 + 4845 x^16 y^4 + 15504 x^15 y^5 + 38760 x^14 y^6 + 77520 x^13 "
      "y^7 + 125970 x^12 y^8 + 167960 x^11 y^9 + 184756 x^10 y^10 + 167960 x^9 y^11 + 125970 x^8 y^12 + 77520 x^7 y^13 "
      "+ 38760 x^6 y^14 + 15504 x^5 y^15 + 4845 x^4 y^16 + 1140 x^3 y^17 + 190 x^2 y^18 + 20 x y^19 + y^20");

  EXPECT_EQ(Expression("(x+y+z)^4").toString(),
            "x^4 + 4 x^3 y + 4 x^3 z + 6 x^2 y^2 + 12 x^2 y z + 6 x^2 z^2 + 4 x y^3 + 12 x y^2 z + 12 x y z^2 + 4 x "
            "z^3 + y^4 + 4 y^3 z + 6 y^2 z^2 + 4 y z^3 + z^4");

  // TODO: for benchmarks
  // EXPECT_EQ(Expression("(2 + 3 * x + 4 * x * y)^60").toString(), "");
  // EXPECT_EQ(Expression("(a+b+c+d)^60").toString(), "");

  EXPECT_EQ(
      Expression(
          "(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+"
          "y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)")
          .toString(),
      "x^30 + 30 x^29 y + 435 x^28 y^2 + 4060 x^27 y^3 + 27405 x^26 y^4 + 142506 x^25 y^5 + 593775 x^24 y^6 + 2035800 "
      "x^23 y^7 + 5852925 x^22 y^8 + 14307150 x^21 y^9 + 30045015 x^20 y^10 + 54627300 x^19 y^11 + 86493225 x^18 y^12 "
      "+ 119759850 x^17 y^13 + 145422675 x^16 y^14 + 155117520 x^15 y^15 + 145422675 x^14 y^16 + 119759850 x^13 y^17 + "
      "86493225 x^12 y^18 + 54627300 x^11 y^19 + 30045015 x^10 y^20 + 14307150 x^9 y^21 + 5852925 x^8 y^22 + 2035800 "
      "x^7 y^23 + 593775 x^6 y^24 + 142506 x^5 y^25 + 27405 x^4 y^26 + 4060 x^3 y^27 + 435 x^2 y^28 + 30 x y^29 + "
      "y^30");

  EXPECT_EQ(
      Expression(
          "(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-"
          "y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)")
          .toString(),
      "x^30 - 30 x^29 y + 435 x^28 y^2 - 4060 x^27 y^3 + 27405 x^26 y^4 - 142506 x^25 y^5 + 593775 x^24 y^6 - 2035800 "
      "x^23 y^7 + 5852925 x^22 y^8 - 14307150 x^21 y^9 + 30045015 x^20 y^10 - 54627300 x^19 y^11 + 86493225 x^18 y^12 "
      "- 119759850 x^17 y^13 + 145422675 x^16 y^14 - 155117520 x^15 y^15 + 145422675 x^14 y^16 - 119759850 x^13 y^17 + "
      "86493225 x^12 y^18 - 54627300 x^11 y^19 + 30045015 x^10 y^20 - 14307150 x^9 y^21 + 5852925 x^8 y^22 - 2035800 "
      "x^7 y^23 + 593775 x^6 y^24 - 142506 x^5 y^25 + 27405 x^4 y^26 - 4060 x^3 y^27 + 435 x^2 y^28 - 30 x y^29 + "
      "y^30");

  EXPECT_EQ(
      Expression("sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
                 "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
                 "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
                 "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
                 "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
                 "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
                 "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
                 "sin(sin(sin(sin(x))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
                 ")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))")
          .toString(),
      "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
      "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
      "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
      "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
      "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
      "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin("
      "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(x)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
      ")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))"
      ")");

  // TODO: for benchmark
  // EXPECT_EQ(Expression("a<->b<->c<->d<->e<->f").toString(),

  EXPECT_EQ(Expression("a<->b<->c<->d<->e").toString(), "(a & b & c & d & e) | "
                                                        "(a & b & c & ~d & ~e) | "
                                                        "(a & b & ~c & d & ~e) | "
                                                        "(a & b & ~c & ~d & e) | "
                                                        "(a & ~b & c & d & ~e) | "
                                                        "(a & ~b & c & ~d & e) | "
                                                        "(a & ~b & ~c & d & e) | "
                                                        "(a & ~b & ~c & ~d & ~e) | "
                                                        "(~a & b & c & d & ~e) | "
                                                        "(~a & b & c & ~d & e) | "
                                                        "(~a & b & ~c & d & e) | "
                                                        "(~a & b & ~c & ~d & ~e) | "
                                                        "(~a & ~b & c & d & e) | "
                                                        "(~a & ~b & c & ~d & ~e) | "
                                                        "(~a & ~b & ~c & d & ~e) | "
                                                        "(~a & ~b & ~c & ~d & e)");

  EXPECT_EQ(Expression("a & b & c & d & e & f & g & h & i & j & k & l & m & n & o & p & q & r & s & t & u & v & w & x "
                       "& y & z & x_1 & x_2 & x_3 | x_4")
                .toString(),
            "(a & b & c & d & e & f & g & h & i & j & k & l & m & n & o & p & q & r & s & t & u & v & w & x & x_1 & "
            "x_2 & x_3 & y & z) | x_4");

  EXPECT_EQ(Expression("a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x "
                       "| y | z | x_1 | x_2 | x_3 & x_4")
                .toString(),
            "a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | x_1 | x_2 "
            "| (x_3 & x_4) | y | z");
}

TEST(ExpressionTests, stringConstructorNegativeTest) {
  EXPECT_THROW(Expression(""), InvalidInputException);
  EXPECT_THROW(Expression("1+"), InvalidInputException);
  EXPECT_THROW(Expression("1-"), InvalidInputException);
  EXPECT_THROW(Expression("1*"), InvalidInputException);
  EXPECT_THROW(Expression("1/"), InvalidInputException);
  EXPECT_THROW(Expression(" +   "), InvalidInputException);
  EXPECT_THROW(Expression("(1+2))"), InvalidInputException);
  EXPECT_THROW(Expression("5-*3"), InvalidInputException);
  EXPECT_THROW(Expression("((()()))"), InvalidInputException);
  EXPECT_THROW(Expression("2.2.2"), InvalidInputException);
  EXPECT_THROW(Expression("--"), InvalidInputException);
  EXPECT_THROW(Expression("."), InvalidInputException);
  EXPECT_THROW(Expression(","), InvalidInputException);
  EXPECT_THROW(Expression("/"), InvalidInputException);
  EXPECT_THROW(Expression(";"), InvalidInputException);
  EXPECT_THROW(Expression("\'"), InvalidInputException);
  EXPECT_THROW(Expression("["), InvalidInputException);
  EXPECT_THROW(Expression("]"), InvalidInputException);
  EXPECT_THROW(Expression("!"), InvalidInputException);
  EXPECT_THROW(Expression("@"), InvalidInputException);
  EXPECT_THROW(Expression("\""), InvalidInputException);
  EXPECT_THROW(Expression("#"), InvalidInputException);
  EXPECT_THROW(Expression("№"), InvalidInputException);
  EXPECT_THROW(Expression("%"), InvalidInputException);
  EXPECT_THROW(Expression(":"), InvalidInputException);
  EXPECT_THROW(Expression("?"), InvalidInputException);
  EXPECT_THROW(Expression("*"), InvalidInputException);
  EXPECT_THROW(Expression("("), InvalidInputException);
  EXPECT_THROW(Expression(")"), InvalidInputException);
  EXPECT_THROW(Expression("-"), InvalidInputException);
  EXPECT_THROW(Expression("+"), InvalidInputException);
  EXPECT_THROW(Expression("$"), InvalidInputException);
  EXPECT_THROW(Expression("^"), InvalidInputException);
  EXPECT_THROW(Expression("&"), InvalidInputException);
  EXPECT_THROW(Expression("_"), InvalidInputException);
  EXPECT_THROW(Expression("[1+1]"), InvalidInputException);
  EXPECT_THROW(Expression("{1}"), InvalidInputException);
  EXPECT_THROW(Expression(",2"), InvalidInputException);
  EXPECT_THROW(Expression("2,"), InvalidInputException);

  EXPECT_THROW(Expression("(1"), InvalidInputException);
  EXPECT_THROW(Expression("(((2)"), InvalidInputException);
  EXPECT_THROW(Expression("(((2))"), InvalidInputException);
  EXPECT_THROW(Expression("((2)))"), InvalidInputException);
  EXPECT_THROW(Expression("(2)))"), InvalidInputException);
  EXPECT_THROW(Expression("(2"), InvalidInputException);
  EXPECT_THROW(Expression("((2)"), InvalidInputException);
  EXPECT_THROW(Expression("((2"), InvalidInputException);
  EXPECT_THROW(Expression("(()())"), InvalidInputException);
  EXPECT_THROW(Expression("((((()))))"), InvalidInputException);
  EXPECT_THROW(Expression("((((2)((2))))"), InvalidInputException);

  EXPECT_THROW(Expression("!2"), InvalidInputException);
  EXPECT_THROW(Expression("!!2"), InvalidInputException);
  EXPECT_THROW(Expression("!2!!"), InvalidInputException);
  EXPECT_THROW(Expression("!(2"), InvalidInputException);
  EXPECT_THROW(Expression("!(2)"), InvalidInputException);
  EXPECT_THROW(Expression("2)!"), InvalidInputException);
  EXPECT_THROW(Expression("sin(2))!"), InvalidInputException);
  EXPECT_THROW(Expression("!!!!!!"), InvalidInputException);

  EXPECT_THROW(Expression("esin()"), InvalidInputException);
  EXPECT_THROW(Expression("(a+b)*()"), InvalidInputException);

  EXPECT_THROW(Expression("sin(2,3)"), InvalidInputException);
  EXPECT_THROW(Expression("sin(,)"), InvalidInputException);
  EXPECT_THROW(Expression("sin(,2)"), InvalidInputException);
  EXPECT_THROW(Expression("sin(2,)"), InvalidInputException);
  EXPECT_THROW(Expression("sin()"), InvalidInputException);
  EXPECT_THROW(Expression("log(1)"), InvalidInputException);
  EXPECT_THROW(Expression("log()"), InvalidInputException);

  EXPECT_THROW(Expression("(1 = 1) / 2"), InvalidInputException);
  EXPECT_THROW(Expression("2 + (1 = 2)"), InvalidInputException);
  EXPECT_THROW(Expression("sin(1 = 1)"), InvalidInputException);
  EXPECT_THROW(Expression("sin(sin(1 = 1))"), InvalidInputException);
  EXPECT_THROW(Expression("sin(sin(sin(1 = 1)))"), InvalidInputException);
  EXPECT_THROW(Expression("True/True"), InvalidInputException);
  EXPECT_THROW(Expression("((1 == 1)) + ((1 == 2))"), InvalidInputException);
  EXPECT_THROW(Expression("((1 == 1)) - ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(Expression("((1 == 1)) / ((1 == 1))"), InvalidInputException);
  EXPECT_THROW(Expression("(5+5)=(2=5)"), InvalidInputException);
  EXPECT_THROW(Expression("1+(sin(x)<2)"), InvalidInputException);
  EXPECT_THROW(Expression("1/(sin(x)<2)"), InvalidInputException);
  EXPECT_THROW(Expression("1+False"), InvalidInputException);
  EXPECT_THROW(Expression("False+1"), InvalidInputException);
  EXPECT_THROW(Expression("1=False"), InvalidInputException);
  EXPECT_THROW(Expression("False=1"), InvalidInputException);
  EXPECT_THROW(Expression("1&2"), InvalidInputException);
  EXPECT_THROW(Expression("x+1&x+2"), InvalidInputException);
  EXPECT_THROW(Expression("x+1&x"), InvalidInputException);
  EXPECT_THROW(Expression("x&x+2"), InvalidInputException);
  EXPECT_THROW(Expression("(x&y)=(y&z)"), InvalidInputException);
  EXPECT_THROW(Expression("derivative(x=y, x)"), InvalidInputException);
  EXPECT_THROW(Expression("derivative(x&y,x)"), InvalidInputException);
  EXPECT_THROW(Expression("derivative(True,a)"), InvalidInputException);
  EXPECT_THROW(Expression("(a+1)_(a>2)"), InvalidInputException);
  EXPECT_THROW(Expression("(x+1)_1"), InvalidInputException);
  EXPECT_THROW(Expression("(x*2)_1"), InvalidInputException);
  EXPECT_THROW(Expression("(x*2)_((x+2)_x)"), InvalidInputException);
  EXPECT_THROW(Expression("x^x_1"), InvalidInputException);
  EXPECT_THROW(Expression("E&a"), InvalidInputException);
  EXPECT_THROW(Expression("~Inf"), InvalidInputException);
  EXPECT_THROW(Expression("~Undefined"), InvalidInputException);
  EXPECT_THROW(Expression("a | Undefined"), InvalidInputException);

  EXPECT_THROW(Expression("min()"), InvalidInputException);
  EXPECT_THROW(Expression("min(True, False)"), InvalidInputException);
  EXPECT_THROW(Expression("max()"), InvalidInputException);
  EXPECT_THROW(Expression("max(True, False)"), InvalidInputException);

  EXPECT_THROW(Expression("(-1)!"), UndefinedException);
  EXPECT_THROW(Expression("(2/3)!"), UndefinedException);
  EXPECT_THROW(Expression("(-1)!!"), UndefinedException);
  EXPECT_THROW(Expression("(2/3)!!"), UndefinedException);
  EXPECT_THROW(Expression("sqrt(-1)"), UndefinedException);
  EXPECT_THROW(Expression("ln(0)"), UndefinedException);
  EXPECT_THROW(Expression("ln(-1)"), UndefinedException);
  EXPECT_THROW(Expression("log(-1, 1)"), UndefinedException);
  EXPECT_THROW(Expression("log(0, 1)"), UndefinedException);
  EXPECT_THROW(Expression("log(1, 0)"), UndefinedException);
  EXPECT_THROW(Expression("lb(-1)"), UndefinedException);
  EXPECT_THROW(Expression("lg(-1)"), UndefinedException);
  EXPECT_THROW(Expression("sqrt(-1)"), UndefinedException);
  EXPECT_THROW(Expression("(-1)^(2/3)"), UndefinedException);
  EXPECT_THROW(Expression("ln(0)"), UndefinedException);
  EXPECT_THROW(Expression("ln(-1)"), UndefinedException);
  EXPECT_THROW(Expression("log(-1, 1)"), UndefinedException);
  EXPECT_THROW(Expression("log(0, 1)"), UndefinedException);
  EXPECT_THROW(Expression("log(1, 0)"), UndefinedException);
  EXPECT_THROW(Expression("lb(-1)"), UndefinedException);
  // TODO constants
  // EXPECT_THROW(Expression("E!"), UndefinedException);
  // EXPECT_THROW(Expression("tan(Pi/2)"), UndefinedException);
  // EXPECT_THROW(Expression("cot(0)"), UndefinedException);
  // EXPECT_THROW(Expression("asin(2)"), UndefinedException);
  // EXPECT_THROW(Expression("acos(2)"), UndefinedException);
  // EXPECT_THROW(Expression("tan(3/2*Pi)"), UndefinedException);
  // EXPECT_THROW(Expression("cot(2*Pi)"), UndefinedException);
}

TEST(ExpressionTests, preciseTest) {
  EXPECT_EQ(Expression("10^10000").precise(8).toString(), "1*10^10000");
  EXPECT_EQ(Expression("x+E").precise(8).toString(), "x + 2.7182818");
  EXPECT_EQ(Expression("x^(100!)").precise(8).toString(), "x^(9.3326215*10^157)");
  EXPECT_EQ(Expression("9^10000").precise(8).toString(), "2.6613034*10^9542");
  EXPECT_EQ(Expression("sin(E)").precise(16).toString(), "0.4107812905029087");
  EXPECT_EQ(Expression("sin(sin(E))").precise(30).toString(), "0.39932574404189139297067052142");
  EXPECT_EQ(Expression("(sqrt(2) + 1)^2").precise(5).toString(), "5.8284");
  EXPECT_EQ(Expression("(sqrt(2) - a - 1)^2").precise(5).toString(), "a^2 - 0.82843 a + 0.17157");
  EXPECT_EQ(Expression("2^200/x").precise(10).toString(), "(1.606938044*10^60)/x");
  EXPECT_EQ(Expression("x/2^200").precise(10).toString(), "6.223015278*10^-61 x");

  EXPECT_EQ(Expression("150!").precise().toString(),
            "5.7133839564458545904789328652610540031895535786011264182548375833179829124845398*10^262");
  EXPECT_EQ(Expression("E").precise().toString(),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
  EXPECT_EQ(Expression("Pi").precise().toString(),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
  EXPECT_EQ(Expression("exp100").precise().toString(),
            "26881171418161354484126255515800135873611118.773741922415191608615280287034909565");
  EXPECT_EQ(Expression("E^101").precise().toString(),
            "73070599793680672726476826340615135890078390.083960707616445859670987728609198428");
  EXPECT_EQ(Expression("E^(-101)").precise().toString(),
            "1.3685394711738530002470557302322944177986775531612023009807438134142551921153897*10^-44");
  EXPECT_EQ(Expression("ln3").precise().toString(),
            "1.098612288668109691395245236922525704647490557822749451734694333637494293218609");
  EXPECT_EQ(Expression("ln2").precise().toString(),
            "0.69314718055994530941723212145817656807550013436025525412068000949339362196969472");
  EXPECT_EQ(Expression("ln100").precise().toString(),
            "4.605170185988091368035982909368728415202202977257545952066655801935145219354705");
  EXPECT_EQ(Expression("lg99").precise().toString(),
            "1.9956351945975499153402557777532548601069599188478448242562702992902113378005716");
  EXPECT_EQ(Expression("lg100").precise().toString(), "2");
  EXPECT_EQ(Expression("lb100").precise().toString(),
            "6.6438561897747246957406388589787803517296627860491612241095127916318695532172504");
  EXPECT_EQ(Expression("lb4").precise().toString(), "2");
  EXPECT_EQ(Expression("sin10").precise().toString(),
            "-0.54402111088936981340474766185137728168364301291622389157418401261675720964049343");
  EXPECT_EQ(Expression("cos10").precise().toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_EQ(Expression("tan10").precise().toString(),
            "0.6483608274590866712591249330098086768168743429837249756336279673958556003746239");
  EXPECT_EQ(Expression("cot10").precise().toString(),
            "1.5423510453569200482774693556824293113206672064019624909194716061981945043136768");
  EXPECT_EQ(Expression("asin0.9").precise().toString(),
            "1.1197695149986341866866770558453996158951621864033028823756818639144375371065333");
  EXPECT_EQ(Expression("acos0.9").precise().toString(),
            "0.45102681179626243254464463579435182620342251328425002811179043223947066603657116");
  EXPECT_EQ(Expression("atan10").precise().toString(),
            "1.4711276743037345918528755717617308518553063771832382624719635193438804556955538");
  EXPECT_EQ(Expression("acot10").precise().toString(),
            "0.099668652491162027378446119878020590243278322504314648015508776810027747447550654");
  EXPECT_EQ(Expression("sinh10").precise().toString(),
            "11013.232874703393377236524554846364402901451190319346103835228548076948583785685");
  EXPECT_EQ(Expression("cosh10").precise().toString(),
            "11013.232920103323139721376090437879963452061428237434970400197807148254234785107");
  EXPECT_EQ(Expression("tanh10").precise().toString(),
            "0.99999999587769276361959283713827574105081461849501996226140069543680188089876683");
  EXPECT_EQ(Expression("coth10").precise().toString(),
            "1.0000000041223072533738241840280803124601800267562193084479187641100667185123807");
  EXPECT_EQ(Expression("asinh0.9").precise().toString(),
            "0.80886693565278246250935016738160604299699494260611658590774273687832265593746445");
  EXPECT_EQ(Expression("acosh1.9").precise().toString(),
            "1.2571958266003804345446952305599900185447096920846764166114358405852412800661934");
  EXPECT_EQ(Expression("atanh0.9").precise().toString(),
            "1.4722194895832202300045137159439267686186896306495644092689801182046463510320986");
  EXPECT_EQ(Expression("acoth1.9").precise().toString(),
            "0.5850356263251273221963907792584300980997658991386225877261408421838960973503172");
  EXPECT_EQ(Expression("((2))*sqrt2").precise().toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");
  EXPECT_EQ(Expression("sqrt2*((2))").precise().toString(),
            "2.8284271247461900976033774484193961571393437507538961463533594759814649569242141");
  EXPECT_EQ(Expression("sin(1)^2").precise().toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin(-1)^2").precise().toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin1^2").precise().toString(),
            "0.70807341827357119349878411475038109488300038553777244537757498689098246806203958");
  EXPECT_EQ(Expression("sin(10^30)").precise().toString(),
            "-0.090116901912138058030386428952987330274396332993043449885460666579773983476795775");
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").precise().toString(), "1"); // TODO: move to str constructor tests
  EXPECT_EQ(Expression("sin(Pi/3)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("cos(Pi/3)").precise().toString(), "0.5"); // TODO: move to str constructor tests
  EXPECT_EQ(Expression("2!*E").precise().toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(Expression("E*2!").precise().toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(Expression("sqrt((1-cos(2*(Pi/3)))/2)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(Pi/3)))/2)*cos(Pi/3)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("1/(sin(5))").precise().toString(),
            "-1.0428352127714058197831198559077598439723517523645461744044708582222288573346961");
  EXPECT_EQ(Expression("sin(60deg)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("((x - z)^2 / 8) * (x / y)").precise().toString(),
            "(0.125 x^3)/y + (-0.25 x^2 z)/y + (0.125 x z^2)/y");

  EXPECT_EQ(Expression("ln(x)").precise().toString(), "ln(x)");
  EXPECT_EQ(Expression("sqrt(x)").precise().toString(), "sqrt(x)");
  EXPECT_EQ(Expression("root(x, 3)").precise().toString(), "root(x, 3)");
  EXPECT_EQ(Expression("root(x, 10)").precise().toString(), "x^0.1");
  EXPECT_EQ(Expression("root(x, 33)").precise().toString(),
            "x^0.03030303030303030303030303030303030303030303030303030303030303030303030303030303");

  // TODO: move to str constructor tests
  EXPECT_EQ(Expression("derivative(sqrt((1-cos(2*(Pi/3)))/2), x)").precise().toString(), "0");
}

TEST(ExpressionTests, preciseNegativeTest) {
  // TODO: move to str constructor negative tests
  EXPECT_THROW(Expression("tan(Pi/2)").precise(), UndefinedException);
  EXPECT_THROW(Expression("cot(0)").precise(), UndefinedException);
  EXPECT_THROW(Expression("asin(2)").precise(), UndefinedException);
  EXPECT_THROW(Expression("acos(2)").precise(), UndefinedException);
  EXPECT_THROW(Expression("tan(3/2*Pi)").precise(), UndefinedException);
  EXPECT_THROW(Expression("cot(2*Pi)").precise(), UndefinedException);

  // TODO: do no perform operation, when the result is too big
  // EXPECT_THROW(Expression("ln(ln(ln(ln(ln(E^(E^(E^(E^E))))))))").precise(), UndefinedException);
}

TEST(ExpressionTests, toMinimalObjectTest) {
  EXPECT_TRUE(is<Variable>(Expression("a").toMinimalObject()));
  EXPECT_TRUE(is<INumber>(Expression("123.123").toMinimalObject()));
  EXPECT_TRUE(is<IExpression>(Expression("a+a").toMinimalObject()));
}

TEST(ExpressionTests, setChildrenTest) {
  Expression expr;

  expr.setChildren({Variable("a").clone()});
  EXPECT_EQ(expr.toString(), "a");

  expr.setChildren({Expression("a-a").clone()});
  EXPECT_EQ(expr.toString(), "0");

  EXPECT_THROW(expr.setChildren({Variable("a").clone(), Variable("b").clone()}), InvalidInputException);
}

TEST(ExpressionTests, equalsTest) {
  Expression a;

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, Expression());
  EXPECT_EQ(Expression(), a);
  EXPECT_EQ(a, cast<IMathObject>(Expression()));
  EXPECT_EQ(cast<IMathObject>(Expression()), a);
  EXPECT_NE(a, Variable("a"));
  EXPECT_NE(Variable("a"), a);

  // TODO: implement more tests
}

TEST(ExpressionTests, variableVariablePlusOperatorTest) {
  EXPECT_EQ(Variable("a") + Variable("a"), Expression("2a"));
  EXPECT_EQ(Variable("a") + Variable("b"), Expression("a+b"));
}

TEST(ExpressionTests, variableExpressionPlusOperatorTest) {
  EXPECT_EQ(Variable("a") + Expression("a+b"), Expression("2a+b"));
  EXPECT_EQ(Variable("a") + Expression("b+c"), Expression("a+b+c"));
}

TEST(ExpressionTests, expressionVariablePlusOperatorTest) {
  EXPECT_EQ(Expression("a+b") + Variable("a"), Expression("2a+b"));
  EXPECT_EQ(Expression("b+c") + Variable("a"), Expression("a+b+c"));
}

TEST(ExpressionTests, variableVariableMinusOperatorTest) {
  EXPECT_EQ(Variable("a") - Variable("a"), Expression("0"));
  EXPECT_EQ(Variable("a") - Variable("b"), Expression("a-b"));
}

TEST(ExpressionTests, variableExpressionMinusOperatorTest) {
  EXPECT_EQ(Variable("a") - Expression("a-b"), Expression("b"));
  EXPECT_EQ(Variable("a") - Expression("b-c"), Expression("a-b+c"));
}

TEST(ExpressionTests, expressionVariableMinusOperatorTest) {
  EXPECT_EQ(Expression("a-b") - Variable("a"), Expression("-b"));
  EXPECT_EQ(Expression("b-c") - Variable("a"), Expression("-a+b-c"));
}

TEST(ExpressionTests, variableVariableMultiplyOperatorTest) {
  EXPECT_EQ(Variable("a") * Variable("a"), Expression("a^2"));
  EXPECT_EQ(Variable("a") * Variable("b"), Expression("ab"));
}

TEST(ExpressionTests, variableExpressionMultiplyOperatorTest) {
  EXPECT_EQ(Variable("a") * Expression("a*b"), Expression("a^2 b"));
  EXPECT_EQ(Variable("a") * Expression("b*c"), Expression("abc"));
}

TEST(ExpressionTests, expressionVariableMultiplyOperatorTest) {
  EXPECT_EQ(Expression("a*b") * Variable("a"), Expression("a^2 b"));
  EXPECT_EQ(Expression("b*c") * Variable("a"), Expression("abc"));
}

TEST(ExpressionTests, variableVariableDivideOperatorTest) {
  EXPECT_EQ(Variable("a") / Variable("a"), Expression("1"));
  EXPECT_EQ(Variable("a") / Variable("b"), Expression("a/b"));
}

TEST(ExpressionTests, variableExpressionDivideOperatorTest) {
  EXPECT_EQ(Variable("a") / Expression("a/b"), Expression("b"));
  EXPECT_EQ(Variable("a") / Expression("b/c"), Expression("(ac)/b"));
}

TEST(ExpressionTests, expressionVariableDivideOperatorTest) {
  EXPECT_EQ(Expression("a/b") / Variable("a"), Expression("1/b"));
  EXPECT_EQ(Expression("b/c") / Variable("a"), Expression("b/c/a"));
}

TEST(ExpressionTests, setVariablesTest) {
  // TODO: implement
}

TEST(ExpressionTests, setVariableTest) {
  Expression a("a+b+c");
  Expression b = a;
  Expression c = a;

  a.setVariable(Variable("a"), 1);
  a.setVariable(Variable("b"), 2);
  a.setVariable(Variable("c"), 3);
  EXPECT_EQ(a.toString(), "6");

  b.setVariable(Variable("d"), 1);
  EXPECT_EQ(b.toString(), "a + b + c");

  c.setVariable(Variable("a"), Expression("ln(b)"));
  c.setVariable(Variable("b"), Expression("E"));
  c.setVariable(Variable("c"), Expression("(a+b)^2"));
  EXPECT_EQ(c.toString(), "a^2 + 2 a b + b^2 + E + 1");
}

TEST(ExpressionTests, getTypeIdTest) {
  EXPECT_EQ(Expression::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Expression));
  EXPECT_EQ(Expression().getTypeId(), MathObjectTypeId(MathObjectType::Expression));
}
