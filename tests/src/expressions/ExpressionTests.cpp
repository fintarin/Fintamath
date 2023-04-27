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

  auto b = move(a);
  EXPECT_TRUE(b.toString() == "3" && &a != &b);

  a = move(b);
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
  // EXPECT_EQ(Expression("1100*4.76%1100*4.76%").toString(), "1713481/625"); // TODO: fix split tokens
  // TODO: implement infinities
  // EXPECT_EQ(Expression("((((((5)/(8)))/(1)))/(((((((9)/(4)))/(0)))/(5))))").toString(), "0");

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
  EXPECT_EQ(Expression("sqrt4!").toString(), "2");
  EXPECT_EQ(Expression("(sqrt4)!").toString(), "2");
  EXPECT_EQ(Expression("sqrt4*2!").toString(), "4");
  EXPECT_EQ(Expression("abs(-5)").toString(), "5");
  EXPECT_EQ(Expression("abs((-5))").toString(), "5");
  EXPECT_EQ(Expression("log(2, 256)").toString(), "ln(256)/ln(2)");
  EXPECT_EQ(Expression("sign(10)").toString(), "1");

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
  EXPECT_EQ(Expression("E^(-101)").toString(), "1/E^101");
  EXPECT_EQ(Expression("log(E,E)").toString(), "1");
  EXPECT_EQ(Expression("log(Pi, Pi^10)").toString(), "ln(Pi^10)/ln(Pi)");
  EXPECT_EQ(Expression("log(E,E^3)").toString(), "ln(E^3)/ln(E)");
  EXPECT_EQ(Expression("log((Pi),(E)^((Pi)))").toString(), "ln(E^Pi)/ln(Pi)");
  EXPECT_EQ(Expression("ln3").toString(), "ln(3)");
  EXPECT_EQ(Expression("ln2").toString(), "ln(2)");
  EXPECT_EQ(Expression("ln100").toString(), "ln(100)");
  EXPECT_EQ(Expression("ln(E)").toString(), "ln(E)");
  EXPECT_EQ(Expression("lg99").toString(), "ln(99)/ln(10)");
  EXPECT_EQ(Expression("lg100").toString(), "ln(100)/ln(10)");
  EXPECT_EQ(Expression("lb100").toString(), "ln(100)/ln(2)");
  EXPECT_EQ(Expression("lb4").toString(), "ln(4)/ln(2)");
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
  EXPECT_EQ(Expression("sqrt((1-cos(2*(Pi/3)))/2)").toString(), "sqrt((-cos((2 Pi)/3) + 1)/2)");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(Pi/3)))/2)*cos(Pi/3)").toString(), "2 cos(Pi/3) sqrt((-cos((2 Pi)/3) + 1)/2)");
  EXPECT_EQ(Expression("ln(ln(ln(ln(E))))").toString(), "ln(ln(ln(ln(E))))");
  EXPECT_EQ(Expression("ln(ln(ln(ln(ln(E)))))").toString(), "ln(ln(ln(ln(ln(E)))))");
  EXPECT_EQ(Expression("-sin(2)").toString(), "-sin(2)");
  EXPECT_EQ(Expression("0^E").toString(), "0");

  EXPECT_EQ(Expression("2.a").toString(), "2 a");
  EXPECT_EQ(Expression("a.2").toString(), "1/5 a");
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
  EXPECT_EQ(Expression("(a+3)/(b+2)").toString(), "(a + 3)/(b + 2)");
  EXPECT_EQ(Expression("b/a*(a+3)/(b+2)").toString(), "(a b)/(a b + 2 a) + (3 b)/(a b + 2 a)");
  EXPECT_EQ(Expression("(5+b)/a*(a+3)/(b+2)").toString(),
            "(a b)/(a b + 2 a) + (5 a)/(a b + 2 a) + (3 b)/(a b + 2 a) + 15/(a b + 2 a)");
  EXPECT_EQ(Expression("(a+b)*(a+b)/(a+b)").toString(), "a + b");
  EXPECT_EQ(Expression("(a+b)*(a+b)*(1/(a+b))").toString(), "a + b");
  // TODO: polynomial division
  //  EXPECT_EQ(Expression("(x^2+2x+1)/(x+1)").toString(), "x + 1");
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
  EXPECT_EQ(Expression("a(2)").toString(), "2 a");
  EXPECT_EQ(Expression("(2)a").toString(), "2 a");
  EXPECT_EQ(Expression("Ea").toString(), "E a");
  EXPECT_EQ(Expression("aE").toString(), "E a");
  EXPECT_EQ(Expression("aEE").toString(), "E^2 a");
  EXPECT_EQ(Expression("EEa").toString(), "E^2 a");
  EXPECT_EQ(Expression("x123").toString(), "123 x");
  EXPECT_EQ(Expression("(a+b(a+b(a+b(a+b))))").toString(), "a b^3 + a b^2 + a b + a + b^4");
  EXPECT_EQ(Expression("(ab+(ab+(ab+(ab))))").toString(), "4 a b");
  EXPECT_EQ(Expression("((a+b+(a+c)+(1+v))+((a+c(abc(aaa))+v)c+d))((c)((d+d+d)b)a)").toString(),
            "3 a^5 b^2 c^4 d + 3 a^2 b c^2 d + 6 a^2 b c d + 3 a b^2 c d + 3 a b c^2 d v + 3 a b c^2 d + 3 a b c d^2 + "
            "3 a b c d v + 3 a b c d");
  EXPECT_EQ(Expression("2/(a + 2) + b/(a + 2)").toString(), "b/(a + 2) + 2/(a + 2)");
  EXPECT_EQ(Expression("c * 2^(a + 2) + b^(a + 2)").toString(), "b^(a + 2) + 2^(a + 2) c");
  EXPECT_EQ(Expression("2^(a + 2) * b^(a + 2)").toString(), "b^(a + 2) 2^(a + 2)");
  EXPECT_EQ(Expression("5/(a+b) + 5/(2a+b) + 5/(a+b)").toString(), "5/(2 a + b) + 10/(a + b)");
  EXPECT_EQ(Expression("(x+y)/(a+b) + 5/(2a+b) + (x+2y)/(a+b)").toString(),
            "(2 x)/(a + b) + (3 y)/(a + b) + 5/(2 a + b)");

  // TODO!
  // EXPECT_EQ(Expression("(a+b+1-1)^1000/(a+b+1-1)^998").toString(), "a^2 + 2 a b + b^2");
  // EXPECT_EQ(Expression("(a+b)^1000/(a+b)^998").toString(), "a^2 + 2 a b + b^2");
  // // TODO: implement function minimization
  // // EXPECT_EQ(Expression("sin(asin(a+b+1-1))^1000/(a+b+1-1)^998").toString(), "sin(asin(a+b))^1000/(a+b)^998");
  // EXPECT_EQ(Expression("a(10^100)/10^99").toString(), "10 a");
  // EXPECT_EQ(Expression("(10+2+3-5)^1000000000a/(9+1)^999999999").toString(), "10 a");
  // EXPECT_EQ(Expression("10^(10^100/10^96)a/10^9999").toString(), "10 a");
  // EXPECT_EQ(Expression("10^(10^100/10^90)a/10^9999999999").toString(), "10 a");
  // EXPECT_EQ(Expression("log(100000000000!,100000000000!)").toString(), "1");

  EXPECT_EQ(Expression("-sin(x)").toString(), "-sin(x)");
  EXPECT_EQ(Expression("-sin(x) + sin(2)").toString(), "-sin(x) + sin(2)");
  EXPECT_EQ(Expression("-3sin(E)").toString(), "-3 sin(E)");
  EXPECT_EQ(Expression("lnE").toString(), "ln(E)");
  EXPECT_EQ(Expression("lncossinE").toString(), "ln(cos(sin(E)))");
  EXPECT_EQ(Expression("ln cos sin a").toString(), "ln(cos(sin(a)))");
  EXPECT_EQ(Expression("1-(sin(x)+1)").toString(), "-sin(x)");
  EXPECT_EQ(Expression("1/(sin(x)+1)").toString(), "1/(sin(x) + 1)");
  EXPECT_EQ(Expression("(x+1)^3").toString(), "x^3 + 3 x^2 + 3 x + 1");
  EXPECT_EQ(Expression("(x+1)^(-3)").toString(), "1/(x^3 + 3 x^2 + 3 x + 1)");
  EXPECT_EQ(Expression("(sin(x)+1)^3").toString(), "sin(x)^3 + 3 sin(x)^2 + 3 sin(x) + 1");
  EXPECT_EQ(Expression("(sin(x)+1)^(-3)").toString(), "1/(sin(x)^3 + 3 sin(x)^2 + 3 sin(x) + 1)");
  EXPECT_EQ(Expression("(sin(x)+1)^(-4)").toString(), "1/(sin(x)^4 + 4 sin(x)^3 + 6 sin(x)^2 + 4 sin(x) + 1)");
  EXPECT_EQ(Expression("(x)sin(a)").toString(), "sin(a) x");
  EXPECT_EQ(Expression("tan(4 a^3 b) + cot(4 a b^3) + b^4 + sin(a^4) + cos(6 a^2 b^2)").toString(),
            "sin(a^4) + tan(4 a^3 b) + cos(6 a^2 b^2) + cot(4 a b^3) + b^4");
  EXPECT_EQ(Expression("tan(4 a^3 b) + cot(sin(4 a b^3)) + b^4 + asin(sin(a^4)) + cos(6 a^2 b^2)").toString(),
            "asin(sin(a^4)) + tan(4 a^3 b) + cos(6 a^2 b^2) + cot(sin(4 a b^3)) + b^4");
  EXPECT_EQ(Expression("tan(4 a_1^3 b) + cot(sin(4 a_1 b^3)) + b^4 + asin(sin(a_1^4)) + cos(6 a_1^2 b^2)").toString(),
            "asin(sin(a_1^4)) + tan(4 a_1^3 b) + cos(6 a_1^2 b^2) + cot(sin(4 a_1 b^3)) + b^4");
  EXPECT_EQ(Expression("a!!!!!!!!!!").toString(), "a!!!!!!!!!!");
  EXPECT_EQ(Expression("a% * a!!! * a! * a!!").toString(), "1/100 a! a!! a!!! a");

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
  EXPECT_EQ(Expression("-6x^2 + 4x - 20 = 15x - 9").toString(), "x^2 + 11/6 x + 11/6 = 0");
  EXPECT_EQ(Expression("2 a^5 b - 4 a b^5  = 0").toString(), "a^5 b - 2 a b^5 = 0");
  EXPECT_EQ(Expression("-2 a^5 b + 4 a b^5  = 0").toString(), "a^5 b - 2 a b^5 = 0");

  EXPECT_EQ(Expression("a'").toString(), "1");
  EXPECT_EQ(Expression("(a+a)'").toString(), "(2 a)'");
  EXPECT_EQ(Expression("b'+a'").toString(), "2");
  EXPECT_EQ(Expression("5'").toString(), "0");

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
  EXPECT_EQ(Expression("a<->a<->a<->a<->a<->a").toString(), "True");
  EXPECT_EQ(Expression("a<->a<->a<->a<->a<->a<->a").toString(), "a");
  EXPECT_EQ(Expression("a&b->b&c").toString(), "~a | (b & c) | ~b");
  EXPECT_EQ(Expression("a&b&c").toString(), "a & b & c");
  EXPECT_EQ(Expression("a&(b&c)").toString(), "a & b & c");
  EXPECT_EQ(Expression("a & ~b & c").toString(), "a & ~b & c");
  EXPECT_EQ(Expression("a | (~b & c)").toString(), "a | (~b & c)");
  EXPECT_EQ(Expression("(a | ~b) & c").toString(), "(a | ~b) & c");
  EXPECT_EQ(Expression("~(a & b)").toString(), "~a | ~b");
  EXPECT_EQ(Expression("~(a | b)").toString(), "~a & ~b");
  EXPECT_EQ(Expression("~(a & b & c)").toString(), "~a | ~b | ~c");
  EXPECT_EQ(Expression("~(a | b | c)").toString(), "~a & ~b & ~c");
  EXPECT_EQ(Expression("~(~a & ~a)").toString(), "a");
  // TODO: improve logic expressions minimization
  // EXPECT_EQ(Expression("~a & b | ~c -> d <-> f !<-> g").toString(),
  //           "((a | ~b) & c | d | f) & ((~a & b | ~c) & ~d | ~f) & g | (((a | ~b) & c | d) & f | (~a & b | ~c) & ~d &
  //           "
  //           "~f) & ~g");
  // EXPECT_EQ(Expression("~~~a & ~~b | ~~~c -> ~~d <-> ~~f !<-> ~~g").toString(),
  //           "((a | ~b) & c | d | f) & ((~a & b | ~c) & ~d | ~f) & g | (((a | ~b) & c | d) & f | (~a & b | ~c) & ~d &
  //           "
  //           "~f) & ~g");
  EXPECT_EQ(Expression("True & b & False & c").toString(), "False");
  EXPECT_EQ(Expression("True | b | False | c").toString(), "True");
  EXPECT_EQ(Expression("(x | ~y | z) & (y | z)").toString(), "(x | ~y | z) & (y | z)");
  EXPECT_EQ(Expression("(x & ~y & z) | (y & z)").toString(), "(x & ~y & z) | (y & z)");
  // TODO: improve logic expressions minimization
  // EXPECT_EQ(Expression("(x | ~y | (x | ~y | z) & (y | z)) & (y | (x & ~y & z) | (y & z))").toString(),
  //           "(x | (x | ~y | z) & (y | z) | ~y) & (x & ~y & z | y | y & z)");
  EXPECT_EQ(Expression("b&c&d | a&c&d | a&b&c").toString(), "(a & b & c) | (a & c & d) | (b & c & d)");
  EXPECT_EQ(Expression("True | a | b | False").toString(), "True");

  EXPECT_EQ(Expression("x=1&a").toString(), "a & x - 1 = 0");
  EXPECT_EQ(Expression("True & a = b").toString(), "a - b = 0");

  EXPECT_EQ(Expression("x_1").toString(), "x_1");
  EXPECT_EQ(Expression("x+x_1").toString(), "x + x_1");
  EXPECT_EQ(Expression("x*x_1").toString(), "x x_1");
  EXPECT_EQ(Expression("x_2^2").toString(), "x_2^2");
  EXPECT_EQ(Expression("sin(x_1)").toString(), "sin(x_1)");
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

  // TODO: improve logic expressions minimization
  // EXPECT_EQ(Expression("a<->b<->c<->d<->e<->f<->g<->h").toString(), "???");

  EXPECT_EQ(
      Expression("(x+y)^20").toString(),
      "x^20 + 20 x^19 y + 190 x^18 y^2 + 1140 x^17 y^3 + 4845 x^16 y^4 + 15504 x^15 y^5 + 38760 x^14 y^6 + 77520 x^13 "
      "y^7 + 125970 x^12 y^8 + 167960 x^11 y^9 + 184756 x^10 y^10 + 167960 x^9 y^11 + 125970 x^8 y^12 + 77520 x^7 y^13 "
      "+ 38760 x^6 y^14 + 15504 x^5 y^15 + 4845 x^4 y^16 + 1140 x^3 y^17 + 190 x^2 y^18 + 20 x y^19 + y^20");

  EXPECT_EQ(Expression("(x+y+z)^4").toString(),
            "x^4 + 4 x^3 y + 6 x^2 y^2 + 12 x^2 y z + 4 x y^3 + 12 x y^2 z + 12 x y z^2 + 4 x^3 z + 6 x^2 z^2 + 4 x "
            "z^3 + y^4 + 4 y^3 z + 6 y^2 z^2 + 4 y z^3 + z^4");

  // TODO: optimize
  // EXPECT_EQ(Expression("(2 + 3 * x + 4 * x * y)^60").toString(), "");

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
  EXPECT_THROW(Expression("(x=y)'"), InvalidInputException);
  EXPECT_THROW(Expression("(x&y)'"), InvalidInputException);
  EXPECT_THROW(Expression("True'"), InvalidInputException);
  EXPECT_THROW(Expression("(a+1)_(a>2)"), InvalidInputException);
  EXPECT_THROW(Expression("(x+1)_1"), InvalidInputException);
  EXPECT_THROW(Expression("(x*2)_1"), InvalidInputException);
  EXPECT_THROW(Expression("(x*2)_((x+2)_x)"), InvalidInputException);
  EXPECT_THROW(Expression("x^x_1"), InvalidInputException);

  EXPECT_THROW(Expression("1/0"), UndefinedException);
  EXPECT_THROW(Expression("a/0"), UndefinedException);
  EXPECT_THROW(Expression("(a/0)/(a/0)"), UndefinedException);
  EXPECT_THROW(Expression("0^0"), UndefinedException);
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
  EXPECT_THROW(Expression("(-1)^(2/3)"), UndefinedException);
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
  EXPECT_EQ(Expression("9^10000").precise(8).toString(), "2.6613034*10^9542");
  EXPECT_EQ(Expression("sin(E)").precise(16).toString(), "0.4107812905029087");
  EXPECT_EQ(Expression("sin(sin(E))").precise(30).toString(), "0.39932574404189139297067052142");
  EXPECT_EQ(Expression("(sqrt(2) + 1)^2").precise(5).toString(), "5.8284");
  EXPECT_EQ(Expression("(sqrt(2) - a - 1)^2").precise(5).toString(), "a^2 - 0.82843 a + 0.17157");

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
  EXPECT_EQ(Expression("log(E,E)").precise().toString(), "1");
  EXPECT_EQ(Expression("log(2, 256)").precise().toString(), "8");
  EXPECT_EQ(Expression("log(Pi, Pi^10)").precise().toString(), "10");
  EXPECT_EQ(Expression("log(E,E^3)").precise().toString(), "3");
  EXPECT_EQ(Expression("ln3").precise().toString(),
            "1.098612288668109691395245236922525704647490557822749451734694333637494293218609");
  EXPECT_EQ(Expression("ln2").precise().toString(),
            "0.69314718055994530941723212145817656807550013436025525412068000949339362196969472");
  EXPECT_EQ(Expression("ln100").precise().toString(),
            "4.605170185988091368035982909368728415202202977257545952066655801935145219354705");
  EXPECT_EQ(Expression("ln(E)").precise().toString(), "1");
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
  EXPECT_EQ(Expression("sin(1)^2+cos(1)^2").precise().toString(), "1");
  EXPECT_EQ(Expression("sin(Pi/3)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("cos(Pi/3)").precise().toString(), "0.5");
  EXPECT_EQ(Expression("2!*E").precise().toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(Expression("E*2!").precise().toString(),
            "5.4365636569180904707205749427053249955144941873999191499339352554481532607070952");
  EXPECT_EQ(Expression("sqrt((1-cos(2*(Pi/3)))/2)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(Pi/3)))/2)*cos(Pi/3)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("degrees(Pi/4)").precise().toString(), "45");
  EXPECT_EQ(Expression("sin(rad(60))").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");
  EXPECT_EQ(Expression("sin(60°)").precise().toString(),
            "0.86602540378443864676372317075293618347140262690519031402790348972596650845440002");

  EXPECT_EQ(Expression("sin(E)=sin(E)").precise().toString(), "True");
  EXPECT_EQ(Expression("sin(E)>sin(E)").precise().toString(), "False");
  EXPECT_EQ(Expression("sin(E)>=sin(E)").precise().toString(), "True");
  EXPECT_EQ(Expression("sin(E)<sin(E)").precise().toString(), "False");
  EXPECT_EQ(Expression("sin(E)<=sin(E)").precise().toString(), "True");
  EXPECT_EQ(Expression("1/(sin(5))").precise().toString(),
            "-1.0428352127714058197831198559077598439723517523645461744044708582222288573346961");
  EXPECT_EQ(Expression("log(E,5)=ln(5)").precise().toString(), "True");
  EXPECT_EQ(Expression("log(E,5)<ln(5)").precise().toString(), "False");
  EXPECT_EQ(Expression("log(E,5)>ln(5)").precise().toString(), "False");
  EXPECT_EQ(Expression("log(E,5)<=ln(5)").precise().toString(), "True");
  EXPECT_EQ(Expression("log(E,5)>=ln(5)").precise().toString(), "True");
  EXPECT_EQ(Expression("(sqrt((1-cos(2*(Pi/3)))/2))'").precise().toString(), "0");

  // TODO logarithms
  // EXPECT_EQ(Expression("ln(ln(ln(ln(E))))").precise().toString(), "0");
  // EXPECT_EQ(Expression("ln(ln(ln(ln(ln(E)))))").precise().toString(), "1");
}

TEST(ExpressionTests, preciseNegativeTest) {
  EXPECT_THROW(Expression("ln(ln(ln(ln(E))))").precise(), UndefinedException);
  EXPECT_THROW(Expression("ln(ln(ln(ln(ln(E)))))").precise(), UndefinedException);
  EXPECT_THROW(Expression("E!").precise(), UndefinedException);
  EXPECT_THROW(Expression("sqrt(-1)").precise(), UndefinedException);
  EXPECT_THROW(Expression("ln(0)").precise(), UndefinedException);
  EXPECT_THROW(Expression("ln(-1)").precise(), UndefinedException);
  EXPECT_THROW(Expression("log(-1, 1)").precise(), UndefinedException);
  EXPECT_THROW(Expression("log(0, 1)").precise(), UndefinedException);
  EXPECT_THROW(Expression("log(1, 0)").precise(), UndefinedException);
  EXPECT_THROW(Expression("lb(-1)").precise(), UndefinedException);
  EXPECT_THROW(Expression("lg(-1)").precise(), UndefinedException);
  EXPECT_THROW(Expression("(-1)^(2/3)").precise(), UndefinedException);
  EXPECT_THROW(Expression("tan(Pi/2)").precise(), UndefinedException);
  EXPECT_THROW(Expression("cot(0)").precise(), UndefinedException);
  EXPECT_THROW(Expression("asin(2)").precise(), UndefinedException);
  EXPECT_THROW(Expression("acos(2)").precise(), UndefinedException);
  EXPECT_THROW(Expression("tan(3/2*Pi)").precise(), UndefinedException);
  EXPECT_THROW(Expression("cot(2*Pi)").precise(), UndefinedException);

  // TODO: do no perform operation, when the result is too big
  // EXPECT_THROW(Expression("ln(ln(ln(ln(ln(E^(E^(E^(E^E))))))))").precise(), UndefinedException);
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

TEST(ExpressionTests, makeFunctionExpressionTest) {
  // TODO: add tests
  //  friend unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);
  //  friend ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);
}

TEST(ExpressionTests, makeRawFunctionExpressionTest) {
  // TODO: add tests
  // friend shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);
}
