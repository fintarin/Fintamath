#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyTests, simplifyTest) {
  EXPECT_EQ(Expression("3 + 5").toString(),
            "8");
  EXPECT_EQ(Expression("3 + -5").toString(),
            "-2");
  EXPECT_EQ(Expression("-3 + 5").toString(),
            "2");
  EXPECT_EQ(Expression("2 * 2").toString(),
            "4");
  EXPECT_EQ(Expression("-2 * 2").toString(),
            "-4");
  EXPECT_EQ(Expression("2 * -2").toString(),
            "-4");
  EXPECT_EQ(Expression("2 * 3!").toString(),
            "12");
  EXPECT_EQ(Expression("1 / 3").toString(),
            "1/3");
  EXPECT_EQ(Expression("0 / 3").toString(),
            "0");
  EXPECT_EQ(Expression("2 ^ 2").toString(),
            "4");
  EXPECT_EQ(Expression("-2 ^ 2").toString(),
            "-4");
  EXPECT_EQ(Expression("2 ^ -2").toString(),
            "1/4");
  EXPECT_EQ(Expression("2 ^ 3!").toString(),
            "40320");
  EXPECT_EQ(Expression("0^1").toString(),
            "0");
  EXPECT_EQ(Expression("2^0").toString(),
            "1");
  EXPECT_EQ(Expression("(-7)^10").toString(),
            "282475249");
  EXPECT_EQ(Expression("2^0").toString(),
            "1");
  EXPECT_EQ(Expression("0.001-0.002").toString(),
            "-1/1000");
  EXPECT_EQ(Expression("(0.004)/(0.002+0.002)").toString(),
            "1");
  EXPECT_EQ(Expression("2 + 2 * 2").toString(),
            "6");
  EXPECT_EQ(Expression("2^2^2^2").toString(),
            "256");
  EXPECT_EQ(Expression("(2 + 2) * 2").toString(),
            "8");
  EXPECT_EQ(Expression("(2-2)").toString(),
            "0");
  EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(),
            "4");
  EXPECT_EQ(Expression("((((2))))").toString(),
            "2");
  EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(),
            "12");
  EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(),
            "16");
  EXPECT_EQ(Expression("-5").toString(),
            "-5");
  EXPECT_EQ(Expression("--5").toString(),
            "5");
  EXPECT_EQ(Expression("---5").toString(),
            "-5");
  EXPECT_EQ(Expression("+5").toString(),
            "5");
  EXPECT_EQ(Expression("5*-3").toString(),
            "-15");
  EXPECT_EQ(Expression("----5+++5").toString(),
            "10");
  EXPECT_EQ(Expression("5----4").toString(),
            "9");
  EXPECT_EQ(Expression("5+-+-4").toString(),
            "9");
  EXPECT_EQ(Expression("5*+++---4").toString(),
            "-20");
  EXPECT_EQ(Expression("1^-1").toString(),
            "1");
  EXPECT_EQ(Expression("1.").toString(),
            "1");
  EXPECT_EQ(Expression(".1").toString(),
            "1/10");
  EXPECT_EQ(Expression("2+.1+.1+1.+1.").toString(),
            "21/5");
  EXPECT_EQ(Expression("1/10^-20").toString(),
            "100000000000000000000");
  EXPECT_EQ(Expression("1/10^--20").toString(),
            "1/100000000000000000000");
  EXPECT_EQ(Expression("1/10^---20").toString(),
            "100000000000000000000");
  EXPECT_EQ(Expression("36/3(8-6)").toString(),
            "24");
  EXPECT_EQ(Expression("36/(8-6)3").toString(),
            "54");
  EXPECT_EQ(Expression("((((((5)/(8)))/(1)))/(((((((9)/(4)))/(0)))/(5))))").toString(),
            "0");
  EXPECT_EQ(Expression("2 mod 2").toString(),
            "0");
  EXPECT_EQ(Expression("5 mod -3").toString(),
            "-1");
  EXPECT_EQ(Expression("-10 mod 4").toString(),
            "2");
  EXPECT_EQ(Expression("-51 mod -11").toString(),
            "-7");
  EXPECT_EQ(Expression("2 mod 3 * 4 / 2").toString(),
            "2");
  EXPECT_EQ(Expression("2 + 3 * 4 mod 5").toString(),
            "4");
  EXPECT_EQ(Expression("2^3 mod 3^2").toString(),
            "8");
  EXPECT_EQ(Expression("2 + 3 * 4 mod 5 / 6").toString(),
            "14 mod (5/6)");
  EXPECT_EQ(Expression("2%").toString(),
            "1/50");
  EXPECT_EQ(Expression("2.35%").toString(),
            "47/2000");
  EXPECT_EQ(Expression("1100*4.76%").toString(),
            "1309/25");
  EXPECT_EQ(Expression("2.35%%%%").toString(),
            "47/2000000000");
  EXPECT_EQ(Expression("1100*4.76%1100*4.76%").toString(),
            "1713481/625");

  EXPECT_EQ(Expression("E").toString(),
            "E");
  EXPECT_EQ(Expression("Pi").toString(),
            "Pi");
  EXPECT_EQ(Expression("E^101-E^101").toString(),
            "0");
  EXPECT_EQ(Expression("E E Pi E").toString(),
            "E^3 Pi");
  EXPECT_EQ(Expression("E Pi E^2 Pi").toString(),
            "E^3 Pi^2");
  EXPECT_EQ(Expression("Pi^5 E^2 Pi").toString(),
            "E^2 Pi^6");
  EXPECT_EQ(Expression("E Pi E^2 Pi^3 E^2 Pi^3 E^5 Pi^5").toString(),
            "E^10 Pi^12");
  EXPECT_EQ(Expression("ln(E^E) / ln(E^E) - 1").toString(),
            "0");
  EXPECT_EQ(Expression("8E").toString(),
            "8 E");
  EXPECT_EQ(Expression("8Pi").toString(),
            "8 Pi");
  EXPECT_EQ(Expression("E8").toString(),
            "8 E");
  EXPECT_EQ(Expression("Pi8").toString(),
            "8 Pi");
  EXPECT_EQ(Expression("exp100").toString(),
            "E^100");
  EXPECT_EQ(Expression("E^101").toString(),
            "E^101");
  EXPECT_EQ(Expression("E^(-101)").toString(),
            "1/(E^101)");
  EXPECT_EQ(Expression("sin10").toString(),
            "sin(10)");
  EXPECT_EQ(Expression("cos10").toString(),
            "cos(10)");
  EXPECT_EQ(Expression("tan10").toString(),
            "tan(10)");
  EXPECT_EQ(Expression("cot10").toString(),
            "cot(10)");
  EXPECT_EQ(Expression("sec10").toString(),
            "sec(10)");
  EXPECT_EQ(Expression("csc10").toString(),
            "csc(10)");
  EXPECT_EQ(Expression("asin0.9").toString(),
            "asin(9/10)");
  EXPECT_EQ(Expression("acos0.9").toString(),
            "acos(9/10)");
  EXPECT_EQ(Expression("atan10").toString(),
            "atan(10)");
  EXPECT_EQ(Expression("acot10").toString(),
            "acot(10)");
  EXPECT_EQ(Expression("asec10").toString(),
            "asec(10)");
  EXPECT_EQ(Expression("acsc10").toString(),
            "acsc(10)");
  EXPECT_EQ(Expression("sinh10").toString(),
            "sinh(10)");
  EXPECT_EQ(Expression("cosh10").toString(),
            "cosh(10)");
  EXPECT_EQ(Expression("tanh10").toString(),
            "tanh(10)");
  EXPECT_EQ(Expression("coth10").toString(),
            "coth(10)");
  EXPECT_EQ(Expression("sech10").toString(),
            "sech(10)");
  EXPECT_EQ(Expression("csch10").toString(),
            "csch(10)");
  EXPECT_EQ(Expression("asinh0.9").toString(),
            "asinh(9/10)");
  EXPECT_EQ(Expression("acosh1.9").toString(),
            "acosh(19/10)");
  EXPECT_EQ(Expression("atanh0.9").toString(),
            "atanh(9/10)");
  EXPECT_EQ(Expression("acoth1.9").toString(),
            "acoth(19/10)");
  EXPECT_EQ(Expression("asech0.9").toString(),
            "asech(9/10)");
  EXPECT_EQ(Expression("acsch1.9").toString(),
            "acsch(19/10)");
  EXPECT_EQ(Expression("((2))*sqrt2").toString(),
            "2 sqrt(2)");
  EXPECT_EQ(Expression("sqrt2*((2))").toString(),
            "2 sqrt(2)");
  EXPECT_EQ(Expression("sin(1)^2").toString(),
            "sin(1)^2");
  EXPECT_EQ(Expression("sin(-1)^2").toString(),
            "sin(1)^2");
  EXPECT_EQ(Expression("sin1^2").toString(),
            "sin(1)^2");
  EXPECT_EQ(Expression("sin(10^30)").toString(),
            "sin(1000000000000000000000000000000)");
  EXPECT_EQ(Expression("sin(1)^2 + cos(1)^2").toString(),
            "1");
  EXPECT_EQ(Expression("3sin(1)^2 + 3cos(1)^2").toString(),
            "3");
  EXPECT_EQ(Expression("2!*E").toString(),
            "2 E");
  EXPECT_EQ(Expression("E*2!").toString(),
            "2 E");
  EXPECT_EQ(Expression("sqrt((1-cos(2*(Pi/3)))/2)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("2*sqrt((1-cos(2*(Pi/3)))/2)*cos(Pi/3)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("-sin(2)").toString(),
            "-sin(2)");
  EXPECT_EQ(Expression("2^(3/2)").toString(),
            "2 sqrt(2)");
  EXPECT_EQ(Expression("sqrt((-1)^2)").toString(),
            "1");
  EXPECT_EQ(Expression("sqrt(sqrt5)").toString(),
            "root(5, 4)");
  EXPECT_EQ(Expression("sqrt(sqrt(-5))").toString(),
            "sqrt(I sqrt(5))");
  EXPECT_EQ(Expression("sqrt4!").toString(),
            "2");
  EXPECT_EQ(Expression("(sqrt4)!").toString(),
            "2");
  EXPECT_EQ(Expression("sqrt4*2!").toString(),
            "4");
  EXPECT_EQ(Expression("abs(-5)").toString(),
            "5");
  EXPECT_EQ(Expression("abs((-5))").toString(),
            "5");
  EXPECT_EQ(Expression("sign(10)").toString(),
            "1");
  EXPECT_EQ(Expression("sign(0)").toString(),
            "0");
  EXPECT_EQ(Expression("sign(-5)").toString(),
            "-1");
  EXPECT_EQ(Expression("frac(2,4)").toString(),
            "1/2");
  EXPECT_EQ(Expression("frac(2,2,4)").toString(),
            "5/2");
  EXPECT_EQ(Expression("sqr(3)").toString(),
            "9");
  EXPECT_EQ(Expression("pow(2,4)").toString(),
            "16");
  EXPECT_EQ(Expression("1deg").toString(),
            "Pi/180");
  EXPECT_EQ(Expression("60deg").toString(),
            "Pi/3");
  EXPECT_EQ(Expression("adeg").toString(),
            "(Pi a)/180");
  EXPECT_EQ(Expression("floor(2/3)").toString(),
            "0");
  EXPECT_EQ(Expression("floor(-2/3)").toString(),
            "-1");
  EXPECT_EQ(Expression("ceil(2/3)").toString(),
            "1");
  EXPECT_EQ(Expression("ceil(-2/3)").toString(),
            "0");
  EXPECT_EQ(Expression("cos(5) - cos(-5)").toString(),
            "0");

  EXPECT_EQ(Expression("x_1").toString(),
            "x_1");
  EXPECT_EQ(Expression("x+x_1").toString(),
            "x + x_1");
  EXPECT_EQ(Expression("x*x_1").toString(),
            "x x_1");
  EXPECT_EQ(Expression("x_2^2").toString(),
            "x_2^2");
  EXPECT_EQ(Expression("sin(x_1)").toString(),
            "sin(x_1)");

  EXPECT_EQ(Expression("a*0").toString(),
            "0");
  EXPECT_EQ(Expression("0*a").toString(),
            "0");
  EXPECT_EQ(Expression("1*a").toString(),
            "a");
  EXPECT_EQ(Expression("a*1").toString(),
            "a");
  EXPECT_EQ(Expression("0^a").toString(),
            "0");
  EXPECT_EQ(Expression("1^a").toString(),
            "1");
  EXPECT_EQ(Expression("(a b)^0").toString(),
            "1");
  EXPECT_EQ(Expression("(a + b)^-1").toString(),
            "1/(a + b)");
  EXPECT_EQ(Expression("(a + b)^-2").toString(),
            "1/(a^2 + 2 a b + b^2)");
  EXPECT_EQ(Expression("(a b)^-1").toString(),
            "1/(a b)");
  EXPECT_EQ(Expression("(a b)^-2").toString(),
            "1/(a^2 b^2)");

  EXPECT_EQ(Expression("2.a").toString(),
            "2 a");
  EXPECT_EQ(Expression("a.2").toString(),
            "a/5");
  EXPECT_EQ(Expression("a+a").toString(),
            "2 a");
  EXPECT_EQ(Expression("a-a").toString(),
            "0");
  EXPECT_EQ(Expression("-a").toString(),
            "-a");
  EXPECT_EQ(Expression("+a").toString(),
            "a");
  EXPECT_EQ(Expression("--a").toString(),
            "a");
  EXPECT_EQ(Expression("---a").toString(),
            "-a");
  EXPECT_EQ(Expression("b--a").toString(),
            "a + b");
  EXPECT_EQ(Expression("b---a").toString(),
            "-a + b");
  EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(),
            "a");
  EXPECT_EQ(Expression("-(-(-(-(-(-(-(-(-a))))))))").toString(),
            "-a");
  EXPECT_EQ(Expression("--------a").toString(),
            "a");
  EXPECT_EQ(Expression("---------a").toString(),
            "-a");
  EXPECT_EQ(Expression("abcdefg").toString(),
            "a b c d e f g");
  EXPECT_EQ(Expression("a+b+c+d+e+f+g").toString(),
            "a + b + c + d + e + f + g");
  EXPECT_EQ(Expression("(a+b)-b").toString(),
            "a");
  EXPECT_EQ(Expression("a-b-c").toString(),
            "a - b - c");
  EXPECT_EQ(Expression("a-(b-c)").toString(),
            "a - b + c");
  EXPECT_EQ(Expression("(a-b)-c").toString(),
            "a - b - c");
  EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(),
            "a^2 + 3 a b + b^2");
  EXPECT_EQ(Expression("x/y/z").toString(),
            "x/(y z)");
  EXPECT_EQ(Expression("x/(y/z)").toString(),
            "(x z)/y");
  EXPECT_EQ(Expression("(x/y)/z").toString(),
            "x/(y z)");
  EXPECT_EQ(Expression("x^y^z").toString(),
            "(x^y)^z");
  EXPECT_EQ(Expression("x^(y^z)").toString(),
            "x^(y^z)");
  EXPECT_EQ(Expression("(x^y)^z").toString(),
            "(x^y)^z");
  EXPECT_EQ(Expression("(a+b)^2").toString(),
            "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("(a+b)^3").toString(),
            "a^3 + 3 a^2 b + 3 a b^2 + b^3");
  EXPECT_EQ(Expression("1*(a+b)^3").toString(),
            "a^3 + 3 a^2 b + 3 a b^2 + b^3");
  EXPECT_EQ(Expression("(a+b)^4").toString(),
            "a^4 + 4 a^3 b + 6 a^2 b^2 + 4 a b^3 + b^4");
  EXPECT_EQ(Expression("5^x 9").toString(),
            "9*5^x");
  EXPECT_EQ(Expression("9 5^x").toString(),
            "9*5^x");
  EXPECT_EQ(Expression("9 5^x 9").toString(),
            "81*5^x");
  EXPECT_EQ(Expression("5^x 99").toString(),
            "99*5^x");
  EXPECT_EQ(Expression("99 5^x").toString(),
            "99*5^x");
  EXPECT_EQ(Expression("99 5^x 99").toString(),
            "9801*5^x");
  EXPECT_EQ(Expression("5^x a").toString(),
            "a 5^x");
  EXPECT_EQ(Expression("a 5^x").toString(),
            "a 5^x");
  EXPECT_EQ(Expression("a 5^x a").toString(),
            "5^x a^2");
  EXPECT_EQ(Expression("2 5^x 6^y 7^z x^2 y^3").toString(),
            "2*5^x 6^y 7^z x^2 y^3");
  EXPECT_EQ(Expression("1*(a+b)*1").toString(),
            "a + b");
  EXPECT_EQ(Expression("-1*(a+b)*1").toString(),
            "-a - b");
  EXPECT_EQ(Expression("1*(a+b)*-1").toString(),
            "-a - b");
  EXPECT_EQ(Expression("-1*(a+b)*-1").toString(),
            "a + b");
  EXPECT_EQ(Expression("1+(a+b)+1").toString(),
            "a + b + 2");
  EXPECT_EQ(Expression("-1+(a+b)+1").toString(),
            "a + b");
  EXPECT_EQ(Expression("1+(a+b)-1").toString(),
            "a + b");
  EXPECT_EQ(Expression("-1+(a+b)-1").toString(),
            "a + b - 2");
  EXPECT_EQ(Expression("2*(a+b)*2").toString(),
            "4 a + 4 b");
  EXPECT_EQ(Expression("-2*(a+b)*2").toString(),
            "-4 a - 4 b");
  EXPECT_EQ(Expression("2*(a+b)*-2").toString(),
            "-4 a - 4 b");
  EXPECT_EQ(Expression("-2*(a+b)*-2").toString(),
            "4 a + 4 b");
  EXPECT_EQ(Expression("2+(a+b)+2").toString(),
            "a + b + 4");
  EXPECT_EQ(Expression("-2+(a+b)+2").toString(),
            "a + b");
  EXPECT_EQ(Expression("2+(a+b)-2").toString(),
            "a + b");
  EXPECT_EQ(Expression("-2+(a+b)-2").toString(),
            "a + b - 4");
  EXPECT_EQ(Expression("(a+b)+(a+b)-(a+b)").toString(),
            "a + b");
  EXPECT_EQ(Expression("(a+b)+(a+b)+(-(a+b))").toString(),
            "a + b");
  EXPECT_EQ(Expression("(a+b)+(a+b)+(-(-(a+b)))").toString(),
            "3 a + 3 b");
  EXPECT_EQ(Expression("-a^2 + b").toString(),
            "-a^2 + b");
  EXPECT_EQ(Expression("-a^2 c + b").toString(),
            "-a^2 c + b");
  EXPECT_EQ(Expression("-a^2 d - a^2 c + b").toString(),
            "-a^2 c - a^2 d + b");
  EXPECT_EQ(Expression("abc").toString(),
            "a b c");
  EXPECT_EQ(Expression("d^abc").toString(),
            "b c d^a");
  EXPECT_EQ(Expression("abc^d").toString(),
            "a b c^d");
  EXPECT_EQ(Expression("(a+b(a+b(a+b(a+b))))").toString(),
            "a b^3 + a b^2 + a b + a + b^4");
  EXPECT_EQ(Expression("(ab+(ab+(ab+(ab))))").toString(),
            "4 a b");
  EXPECT_EQ(Expression("((a+b+(a+c)+(1+v))+((a+c(abc(aaa))+v)c+d))((c)((d+d+d)b)a)").toString(),
            "3 a^5 b^2 c^4 d + 3 a^2 b c^2 d + 6 a^2 b c d + 3 a b^2 c d + 3 a b c^2 d v + 3 a b c^2 d + 3 a b c d^2 + "
            "3 a b c d v + 3 a b c d");
  EXPECT_EQ(Expression("2/(a + 2) + b/(a + 2)").toString(),
            "(b + 2)/(a + 2)");
  EXPECT_EQ(Expression("c * 2^(a + 2) + b^(a + 2)").toString(),
            "b^(a + 2) + 2^(a + 2) c");
  EXPECT_EQ(Expression("2^(a + 2) * b^(a + 2)").toString(),
            "b^(a + 2) 2^(a + 2)");
  EXPECT_EQ(Expression("2 a b c + a b + a b c").toString(),
            "3 a b c + a b");

  EXPECT_EQ(Expression("2%a").toString(),
            "a/50");
  EXPECT_EQ(Expression("2!!!!a!!!").toString(),
            "2 a!!!");
  EXPECT_EQ(Expression("sin a").toString(),
            "sin(a)");
  EXPECT_EQ(Expression("s i n a").toString(),
            "a i n s");
  EXPECT_EQ(Expression("a(2)").toString(),
            "2 a");
  EXPECT_EQ(Expression("(2)a").toString(),
            "2 a");
  EXPECT_EQ(Expression("Ea").toString(),
            "E a");
  EXPECT_EQ(Expression("aE").toString(),
            "E a");
  EXPECT_EQ(Expression("aEE").toString(),
            "E^2 a");
  EXPECT_EQ(Expression("EEa").toString(),
            "E^2 a");
  EXPECT_EQ(Expression("x123").toString(),
            "123 x");
  EXPECT_EQ(Expression("x^y!").toString(),
            "(x^y)!");
  EXPECT_EQ(Expression("lnE").toString(),
            "1");
  EXPECT_EQ(Expression("lncossinE").toString(),
            "ln(cos(sin(E)))");
  EXPECT_EQ(Expression("ln cos sin a").toString(),
            "ln(cos(sin(a)))");
  EXPECT_EQ(Expression("frac(x,y)").toString(),
            "x/y");
  EXPECT_EQ(Expression("pow(x,y)").toString(),
            "x^y");
  EXPECT_EQ(Expression("frac(x,y,z)").toString(),
            "x + y/z");

  EXPECT_EQ(Expression("sqrt(x) + x").toString(),
            "x + sqrt(x)");
  EXPECT_EQ(Expression("sqrt(x) - x").toString(),
            "-x + sqrt(x)");
  EXPECT_EQ(Expression("sqrt(x) * sqrt(x)").toString(),
            "x");
  EXPECT_EQ(Expression("x/(sqrt(x) - x)").toString(),
            "-1 - sqrt(x)/(x - sqrt(x))");
  EXPECT_EQ(Expression("x/(2 sqrt(x) - x)").toString(),
            "-1 - (2 sqrt(x))/(x - 2 sqrt(x))");
  EXPECT_EQ(Expression("(x-1)/(sqrt(x) - x)").toString(),
            "-1 - 1/sqrt(x)");
  EXPECT_EQ(Expression("(x-1)/(2 sqrt(x) - x)").toString(),
            "-1 - (2 sqrt(x) - 1)/(x - 2 sqrt(x))");
  EXPECT_EQ(Expression("(x-1)/(sqrt(x)/2 - x)").toString(),
            "-1 - (sqrt(x) - 2)/(2 x - sqrt(x))");
  EXPECT_EQ(Expression("(x-1)/(root(x, 3) - x)").toString(),
            "-1 - (root(x, 3) - 1)/(x - root(x, 3))");
  EXPECT_EQ(Expression("(x-1)/(2 root(x, 3) - x)").toString(),
            "-1 - (2 root(x, 3) - 1)/(x - 2 root(x, 3))");
  EXPECT_EQ(Expression("(x-1)/(root(x, 3)/2 - x)").toString(),
            "-1 - (root(x, 3) - 2)/(2 x - root(x, 3))");
  EXPECT_EQ(Expression("(x-1)/(x^(4/3) - x)").toString(),
            "(x - 1)/(x^(4/3) - x)");
  EXPECT_EQ(Expression("(x-1)/(2 x^(4/3) - x)").toString(),
            "(x - 1)/(2 x^(4/3) - x)");
  EXPECT_EQ(Expression("x (sqrt(2) + sqrt(3))").toString(),
            "(sqrt(3) + sqrt(2)) x");
  EXPECT_EQ(Expression("x (sqrt(2) + sqrt(3)) y sqrt(2)").toString(),
            "(sqrt(6) + 2) x y");
  EXPECT_EQ(Expression("a + sqrt(2) x + sqrt(3) x + Pi^4 x + 1").toString(),
            "a + (Pi^4 + sqrt(3) + sqrt(2)) x + 1");
  EXPECT_EQ(Expression("a - sqrt(2) x - sqrt(3) x - Pi^4 x + 1").toString(),
            "a + (-Pi^4 - sqrt(3) - sqrt(2)) x + 1");
  EXPECT_EQ(Expression("x Pi^4 ln(5) + x E^2 sin(1) sinh(2)").toString(),
            "(E^2 sin(1) sinh(2) + Pi^4 ln(5)) x");
  EXPECT_EQ(Expression("(a+b) (-sqrt2 + sqrt3 - sqrt5)").toString(),
            "(sqrt(3) - sqrt(5) - sqrt(2)) a + (sqrt(3) - sqrt(5) - sqrt(2)) b");
  EXPECT_EQ(Expression("(sqrt(2) x + sqrt(3) x + Pi^4 x + 1) / (sqrt(2) + sqrt(3) + Pi^4)").toString(),
            "x + 1/(Pi^4 + sqrt(3) + sqrt(2))");
  EXPECT_EQ(Expression("sqrt(1/(7 + x^2)) + sqrt(x)/(sqrt(x) + 1)").toString(),
            "sqrt(1/(x^2 + 7)) + 1 - 1/(sqrt(x) + 1)");
  EXPECT_EQ(Expression("root(1/(7 + x^2), 3) + sqrt(x)/(sqrt(x) + 1)").toString(),
            "root(1/(x^2 + 7), 3) + 1 - 1/(sqrt(x) + 1)");
  EXPECT_EQ(Expression("ln(a) (2x + 2)").toString(),
            "ln(a) (2 x + 2)");
  EXPECT_EQ(Expression("log(a, 2) (2x + 2)").toString(),
            "log(a, 2) (2 x + 2)");
  EXPECT_EQ(Expression("x / (t sin(x))").toString(),
            "(x csc(x))/t");
  EXPECT_EQ(Expression("root(x, x) mod 1").toString(),
            "root(x, x) mod 1");
  EXPECT_EQ(Expression("root(x, y/x) mod 1").toString(),
            "(x^(x/y)) mod 1");

  EXPECT_EQ(Expression("(a+b+1-1)^1000/(a+b+1-1)^998").toString(),
            "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("(a+b)^1000/(a+b)^998").toString(),
            "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("sin(asin(a+b+1-1))^1000/(a+b+1-1)^998").toString(),
            "a^2 + 2 a b + b^2");
  EXPECT_EQ(Expression("a(10^100)/10^99").toString(),
            "10 a");

  EXPECT_EQ(Expression("-sin(x)").toString(),
            "-sin(x)");
  EXPECT_EQ(Expression("-sin(x) + sin(2)").toString(),
            "-sin(x) + sin(2)");
  EXPECT_EQ(Expression("-3sin(E)").toString(),
            "-3 sin(E)");
  EXPECT_EQ(Expression("1-(sin(x)+1)").toString(),
            "-sin(x)");
  EXPECT_EQ(Expression("1/(sin(x)+1)").toString(),
            "1/(sin(x) + 1)");
  EXPECT_EQ(Expression("(x+1)^3").toString(),
            "x^3 + 3 x^2 + 3 x + 1");
  EXPECT_EQ(Expression("(x+1)^(-3)").toString(),
            "1/(x^3 + 3 x^2 + 3 x + 1)");
  EXPECT_EQ(Expression("(sin(x)+1)^3").toString(),
            "sin(x)^3 + 3 sin(x)^2 + 3 sin(x) + 1");
  EXPECT_EQ(Expression("(sin(x)+1)^(-3)").toString(),
            "1/(sin(x)^3 + 3 sin(x)^2 + 3 sin(x) + 1)");
  EXPECT_EQ(Expression("(sin(x)+1)^(-4)").toString(),
            "1/(sin(x)^4 + 4 sin(x)^3 + 6 sin(x)^2 + 4 sin(x) + 1)");
  EXPECT_EQ(Expression("(x)sin(a)").toString(),
            "sin(a) x");
  EXPECT_EQ(Expression("tan(4 a^3 b) + cot(4 a b^3) + b^4 + sin(a^4) + cos(6 a^2 b^2)").toString(),
            "b^4 + sin(a^4) + cos(6 a^2 b^2) + tan(4 a^3 b) + cot(4 a b^3)");
  EXPECT_EQ(Expression("tan(4 a^3 b) + cot(sin(4 a b^3)) + b^4 + asin(sin(a^4)) + cos(6 a^2 b^2)").toString(),
            "b^4 + cos(6 a^2 b^2) + tan(4 a^3 b) + cot(sin(4 a b^3)) + asin(sin(a^4))");
  EXPECT_EQ(Expression("tan(4 a_1^3 b) + cot(sin(4 a_1 b^3)) + b^4 + asin(sin(a_1^4)) + cos(6 a_1^2 b^2)").toString(),
            "b^4 + cos(6 a_1^2 b^2) + tan(4 a_1^3 b) + cot(sin(4 a_1 b^3)) + asin(sin(a_1^4))");
  EXPECT_EQ(Expression("a!!!!!!!!!!").toString(),
            "a!!!!!!!!!!");
  EXPECT_EQ(Expression("a% * a!!! * a! * a!!").toString(),
            "(a a! a!! a!!!)/100");
  EXPECT_EQ(Expression("a! sin(a)").toString(),
            "a! sin(a)");
  EXPECT_EQ(Expression("sin(a) a!").toString(),
            "a! sin(a)");
  EXPECT_EQ(Expression("sin(a) a").toString(),
            "a sin(a)");
  EXPECT_EQ(Expression("a sin(a)").toString(),
            "a sin(a)");
  EXPECT_EQ(Expression("cos(b) sin(a)").toString(),
            "sin(a) cos(b)");
  EXPECT_EQ(Expression("cos(b) log(b, a)").toString(),
            "log(b, a) cos(b)");
  EXPECT_EQ(Expression("cos(a) log(b, c)").toString(),
            "log(b, c) cos(a)");
  EXPECT_EQ(Expression("cos(b^2) log(b, c)").toString(),
            "log(b, c) cos(b^2)");
  EXPECT_EQ(Expression("(x + y^3)^2 * sin(x)/ln(2)/x^2 - (2 sin(x) y^3)/(x ln(2))").toString(),
            "sin(x)/ln(2) + (y^6 sin(x))/(x^2 ln(2))");

  EXPECT_EQ(Expression("1 / (1 - tan(2))").toString(),
            "cos(2)/(cos(2) - sin(2))");
  EXPECT_EQ(Expression("1 / (1 - cot(2))").toString(),
            "sin(2)/(sin(2) - cos(2))");
  EXPECT_EQ(Expression("1 / (1 - tanh(2))").toString(),
            "cosh(2)/(cosh(2) - sinh(2))");
  EXPECT_EQ(Expression("1 / (1 - coth(2))").toString(),
            "sinh(2)/(sinh(2) - cosh(2))");
  EXPECT_EQ(Expression("1 / (1 - sec(2))").toString(),
            "cos(2)/(cos(2) - 1)");
  EXPECT_EQ(Expression("1 / (1 - csc(2))").toString(),
            "sin(2)/(sin(2) - 1)");
  EXPECT_EQ(Expression("1 / (1 - sech(2))").toString(),
            "cosh(2)/(cosh(2) - 1)");
  EXPECT_EQ(Expression("1 / (1 - csch(2))").toString(),
            "sinh(2)/(sinh(2) - 1)");

  EXPECT_EQ(Expression("floor(E)").toString(),
            "2");
  EXPECT_EQ(Expression("ceil(E)").toString(),
            "3");
  EXPECT_EQ(Expression("floor(E^10)").toString(),
            "22026");
  EXPECT_EQ(Expression("ceil(E^10)").toString(),
            "22027");
  EXPECT_EQ(Expression("floor(11^10)").toString(),
            "25937424601");
  EXPECT_EQ(Expression("ceil(11^10)").toString(),
            "25937424601");
  EXPECT_EQ(Expression("tan(floor(E/3))").toString(),
            "0");
  EXPECT_EQ(Expression("tan(ceil(-E/3))").toString(),
            "0");
  EXPECT_EQ(Expression("ln(floor(E/3))").toString(),
            "-Inf");
  EXPECT_EQ(Expression("root(ceil(-E/3), 3)").toString(),
            "0");
  EXPECT_EQ(Expression("floor(E + I)").toString(),
            "2 + I");
  EXPECT_EQ(Expression("floor(E + x)").toString(),
            "floor(x + E)");

  EXPECT_EQ(Expression("abs(E)").toString(),
            "abs(E)");
  EXPECT_EQ(Expression("sign(E)").toString(),
            "1");
  EXPECT_EQ(Expression("abs(-E)").toString(),
            "abs(E)");
  EXPECT_EQ(Expression("sign(-E)").toString(),
            "-1");
  EXPECT_EQ(Expression("abs(E + I)").toString(),
            "abs(E + I)");
  EXPECT_EQ(Expression("sign(E + I)").toString(),
            "sign(E + I)");

  EXPECT_EQ(Expression("floor(-x)").toString(),
            "-ceil(x)");
  EXPECT_EQ(Expression("ceil(-x)").toString(),
            "-floor(x)");
  EXPECT_EQ(Expression("abs(-x)").toString(),
            "abs(x)");
  EXPECT_EQ(Expression("sign(-x)").toString(),
            "-sign(x)");

  EXPECT_EQ(Expression("floor(E^(E^(E^2)))").toString(),
            "floor(E^(E^(E^2)))");
  EXPECT_EQ(Expression("ceil(E^(E^(E^2)))").toString(),
            "ceil(E^(E^(E^2)))");
  EXPECT_EQ(Expression("sign(E^(E^(E^2)))").toString(),
            "1");
}

TEST(SimplifyTests, simplifyLargeTest) {
  EXPECT_EQ(Expression("10^-500").toString(),
            "1/100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

  EXPECT_EQ(Expression("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------a").toString(),
            "a");

  EXPECT_EQ(Expression("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------a").toString(),
            "-a");

  EXPECT_EQ(Expression("a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a+a").toString(),
            "266 a");

  EXPECT_EQ(Expression("(x+y)^20").toString(),
            "x^20 + 20 x^19 y + 190 x^18 y^2 + 1140 x^17 y^3 + 4845 x^16 y^4 + 15504 x^15 y^5 + 38760 x^14 y^6 + 77520 x^13 y^7 + 125970 x^12 y^8 + 167960 x^11 y^9 + 184756 x^10 y^10 + 167960 x^9 y^11 + 125970 x^8 y^12 + 77520 x^7 y^13 + 38760 x^6 y^14 + 15504 x^5 y^15 + 4845 x^4 y^16 + 1140 x^3 y^17 + 190 x^2 y^18 + 20 x y^19 + y^20");

  EXPECT_EQ(Expression("(x+y+z)^4").toString(),
            "x^4 + 4 x^3 y + 4 x^3 z + 6 x^2 y^2 + 12 x^2 y z + 6 x^2 z^2 + 4 x y^3 + 12 x y^2 z + 12 x y z^2 + 4 x z^3 + y^4 + 4 y^3 z + 6 y^2 z^2 + 4 y z^3 + z^4");

  EXPECT_EQ(Expression("(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)(x+y)").toString(),
            "x^30 + 30 x^29 y + 435 x^28 y^2 + 4060 x^27 y^3 + 27405 x^26 y^4 + 142506 x^25 y^5 + 593775 x^24 y^6 + 2035800 x^23 y^7 + 5852925 x^22 y^8 + 14307150 x^21 y^9 + 30045015 x^20 y^10 + 54627300 x^19 y^11 + 86493225 x^18 y^12 + 119759850 x^17 y^13 + 145422675 x^16 y^14 + 155117520 x^15 y^15 + 145422675 x^14 y^16 + 119759850 x^13 y^17 + 86493225 x^12 y^18 + 54627300 x^11 y^19 + 30045015 x^10 y^20 + 14307150 x^9 y^21 + 5852925 x^8 y^22 + 2035800 x^7 y^23 + 593775 x^6 y^24 + 142506 x^5 y^25 + 27405 x^4 y^26 + 4060 x^3 y^27 + 435 x^2 y^28 + 30 x y^29 + y^30");

  EXPECT_EQ(Expression("(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)(x-y)").toString(),
            "x^30 - 30 x^29 y + 435 x^28 y^2 - 4060 x^27 y^3 + 27405 x^26 y^4 - 142506 x^25 y^5 + 593775 x^24 y^6 - 2035800 x^23 y^7 + 5852925 x^22 y^8 - 14307150 x^21 y^9 + 30045015 x^20 y^10 - 54627300 x^19 y^11 + 86493225 x^18 y^12 - 119759850 x^17 y^13 + 145422675 x^16 y^14 - 155117520 x^15 y^15 + 145422675 x^14 y^16 - 119759850 x^13 y^17 + 86493225 x^12 y^18 - 54627300 x^11 y^19 + 30045015 x^10 y^20 - 14307150 x^9 y^21 + 5852925 x^8 y^22 - 2035800 x^7 y^23 + 593775 x^6 y^24 - 142506 x^5 y^25 + 27405 x^4 y^26 - 4060 x^3 y^27 + 435 x^2 y^28 - 30 x y^29 + y^30");

  EXPECT_EQ(Expression("sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(x)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))").toString(),
            "sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(sin(x)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))");

  // TODO: for benchmarks
  // EXPECT_EQ(Expression("(2 + 3 * x + 4 * x * y)^60").toString(),
  //           "");
  // EXPECT_EQ(Expression("(a+b+c+d)^60").toString(),
  //           "");
}
