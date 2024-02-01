#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyComplexNumberTests, simplifyTest) {
  EXPECT_EQ(Expression("(1 + 2I) + (2 + 3I)").toString(),
            "3 + 5 I");
  EXPECT_EQ(Expression("(1 + 2I) - (2 + 3I)").toString(),
            "-1 - I");
  EXPECT_EQ(Expression("(1 + 2I) * (2 + 3I)").toString(),
            "-4 + 7 I");
  EXPECT_EQ(Expression("(1 + 2I) / (2 + 3I)").toString(),
            "8/13 + 1/13 I");
  EXPECT_EQ(Expression("-(2 + 3I)").toString(),
            "-2 - 3 I");
  EXPECT_EQ(Expression("+(2 + 3I)").toString(),
            "2 + 3 I");

  EXPECT_EQ(Expression("(-5 + 2I)^0").toString(),
            "1");
  EXPECT_EQ(Expression("(-5 + 2I)^1").toString(),
            "-5 + 2 I");
  EXPECT_EQ(Expression("(-5 + 2I)^2").toString(),
            "21 - 20 I");
  EXPECT_EQ(Expression("(-5 + 2I)^3").toString(),
            "-65 + 142 I");
  EXPECT_EQ(Expression("(-5 + 2I)^4").toString(),
            "41 - 840 I");
  EXPECT_EQ(Expression("(-5 + 2I)^5").toString(),
            "1475 + 4282 I");
  EXPECT_EQ(Expression("(-5 + 2I)^6").toString(),
            "-15939 - 18460 I");
  EXPECT_EQ(Expression("(-5 + 2I)^7").toString(),
            "116615 + 60422 I");
  EXPECT_EQ(Expression("(-5 + 2I)^8").toString(),
            "-703919 - 68880 I");
  EXPECT_EQ(Expression("(-5 + 2I)^32").toString(),
            "231439382100320515840321 + 95179357018581597343680 I");
  EXPECT_EQ(Expression("(-5 + 2I)^-1").toString(),
            "-5/29 - 2/29 I");
  EXPECT_EQ(Expression("(-5 + 2I)^-5").toString(),
            "1475/20511149 - 4282/20511149 I");
  EXPECT_EQ(Expression("(-5 + 2I)^-6").toString(),
            "-15939/594823321 + 18460/594823321 I");
  EXPECT_EQ(Expression("(-5 + 2I)^-32").toString(),
            "231439382100320515840321/62623297589448778360828428329074752308805325441 - 95179357018581597343680/62623297589448778360828428329074752308805325441 I");

  EXPECT_EQ(Expression("sqrt(-1)").toString(),
            "I");
  EXPECT_EQ(Expression("sqrt(-4) - 5").toString(),
            "-5 + 2 I");
  // TODO: implement
  EXPECT_EQ(Expression("root(-1, 3)").toString(),
            "root(-1, 3)");
  EXPECT_EQ(Expression("root(-1, 4)").toString(),
            "root(-1, 4)");
  EXPECT_EQ(Expression("root(-1, 5)").toString(),
            "root(-1, 5)");
  EXPECT_EQ(Expression("root(-1, 6)").toString(),
            "root(-1, 6)");
  EXPECT_EQ(Expression("root(-1, 7)").toString(),
            "root(-1, 7)");
  EXPECT_EQ(Expression("(-1)^(3/2)").toString(),
            "(-1)^(3/2)");
  EXPECT_EQ(Expression("(-1)^(2/3)").toString(),
            "(-1)^(2/3)");
  EXPECT_EQ(Expression("(-1)^(3/4)").toString(),
            "(-1)^(3/4)");
  EXPECT_EQ(Expression("(-1)^(4/5)").toString(),
            "(-1)^(4/5)");
  EXPECT_EQ(Expression("(-1)^(5/6)").toString(),
            "(-1)^(5/6)");
  EXPECT_EQ(Expression("(-1)^(6/7)").toString(),
            "(-1)^(6/7)");
  EXPECT_EQ(Expression("sqrt(-3) sqrt(-3)").toString(),
            "-3");
  EXPECT_EQ(Expression("sqrt(-3) sqrt(-2)").toString(),
            "-sqrt(6)");
  EXPECT_EQ(Expression("sqrt(I+1) sqrt(I+1)").toString(),
            "1 + I");
  EXPECT_EQ(Expression("sqrt(I+1) sqrt(I)").toString(),
            "sqrt(1 + I) sqrt(I)");
  EXPECT_EQ(Expression("root(-3, 3) root(-3, 3)").toString(),
            "(-3)^(2/3)");
  EXPECT_EQ(Expression("root(-3, 3) root(-2, 3)").toString(),
            "root(-2, 3) root(-3, 3)");
  EXPECT_EQ(Expression("root(I+1, 3) root(I+1, 3)").toString(),
            "(1 + I)^(2/3)");
  EXPECT_EQ(Expression("root(I+1, 3) root(I, 3)").toString(),
            "root(1 + I, 3) root(I, 3)");

  // TODO: implement
  EXPECT_EQ(Expression("ln(-1)").toString(),
            "ln(-1)");
  EXPECT_EQ(Expression("lb(-1)").toString(),
            "log(2, -1)");
  EXPECT_EQ(Expression("lg(-1)").toString(),
            "log(10, -1)");

  // TODO: implement
  EXPECT_EQ(Expression("asin(2)").toString(),
            "asin(2)");
  EXPECT_EQ(Expression("acos(2)").toString(),
            "acos(2)");

  EXPECT_EQ(Expression("abs(I)").toString(),
            "1");
  EXPECT_EQ(Expression("abs(I + 1)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("abs(3I + 2)").toString(),
            "sqrt(13)");

  EXPECT_EQ(Expression("sign(I)").toString(),
            "I");
  EXPECT_EQ(Expression("sign(I + 1)").toString(),
            "((1 + I) sqrt(2))/2");
  EXPECT_EQ(Expression("sign(3I + 2)").toString(),
            "((2 + 3 I) sqrt(13))/13");

  // TODO: implement
  EXPECT_EQ(Expression("sin(I + 1)").toString(),
            "sin(1 + I)");
  EXPECT_EQ(Expression("cos(I + 1)").toString(),
            "cos(1 + I)");
  EXPECT_EQ(Expression("tan(I + 1)").toString(),
            "tan(1 + I)");
  EXPECT_EQ(Expression("cot(I + 1)").toString(),
            "cot(1 + I)");
  EXPECT_EQ(Expression("sec(I + 1)").toString(),
            "sec(1 + I)");
  EXPECT_EQ(Expression("csc(I + 1)").toString(),
            "csc(1 + I)");
  EXPECT_EQ(Expression("asin(I + 1)").toString(),
            "asin(1 + I)");
  EXPECT_EQ(Expression("acos(I + 1)").toString(),
            "acos(1 + I)");
  EXPECT_EQ(Expression("atan(I + 1)").toString(),
            "atan(1 + I)");
  EXPECT_EQ(Expression("acot(I + 1)").toString(),
            "acot(1 + I)");
  EXPECT_EQ(Expression("asec(I + 1)").toString(),
            "asec(1 + I)");
  EXPECT_EQ(Expression("acsc(I + 1)").toString(),
            "acsc(1 + I)");
  EXPECT_EQ(Expression("sinh(I + 1)").toString(),
            "sinh(1 + I)");
  EXPECT_EQ(Expression("cosh(I + 1)").toString(),
            "cosh(1 + I)");
  EXPECT_EQ(Expression("tanh(I + 1)").toString(),
            "tanh(1 + I)");
  EXPECT_EQ(Expression("coth(I + 1)").toString(),
            "coth(1 + I)");
  EXPECT_EQ(Expression("sech(I + 1)").toString(),
            "sech(1 + I)");
  EXPECT_EQ(Expression("csch(I + 1)").toString(),
            "csch(1 + I)");
  EXPECT_EQ(Expression("asinh(I + 1)").toString(),
            "asinh(1 + I)");
  EXPECT_EQ(Expression("acosh(I + 1)").toString(),
            "acosh(1 + I)");
  EXPECT_EQ(Expression("atanh(I + 1)").toString(),
            "atanh(1 + I)");
  EXPECT_EQ(Expression("acoth(I + 1)").toString(),
            "acoth(1 + I)");
  EXPECT_EQ(Expression("asech(I + 1)").toString(),
            "asech(1 + I)");
  EXPECT_EQ(Expression("acsch(I + 1)").toString(),
            "acsch(1 + I)");

  EXPECT_EQ(Expression("sqrt(3) (2/3 + 1/2 I)").toString(),
            "((4 + 3 I) sqrt(3))/6");
  EXPECT_EQ(Expression("I / x").toString(),
            "I/x");
  EXPECT_EQ(Expression("-I / x").toString(),
            "-I/x");
  EXPECT_EQ(Expression("2I / x").toString(),
            "(2 I)/x");
  EXPECT_EQ(Expression("-2I / x").toString(),
            "-(2 I)/x");
  EXPECT_EQ(Expression("(5/6 I) x").toString(),
            "(5 I x)/6");
  EXPECT_EQ(Expression("(5/6 I + 2/7) x").toString(),
            "((12 + 35 I) x)/42");
  EXPECT_EQ(Expression("(5/6 I + 2) x").toString(),
            "((12 + 5 I) x)/6");
  EXPECT_EQ(Expression("(5 I + 2/7) x").toString(),
            "((2 + 35 I) x)/7");
  EXPECT_EQ(Expression("(5/6 I) / x").toString(),
            "(5 I)/(6 x)");
  EXPECT_EQ(Expression("(5/6 I + 2/7) / x").toString(),
            "(12 + 35 I)/(42 x)");
  EXPECT_EQ(Expression("(5/6 I + 2) / x").toString(),
            "(12 + 5 I)/(6 x)");
  EXPECT_EQ(Expression("(5 I + 2/7) / x").toString(),
            "(2 + 35 I)/(7 x)");
  EXPECT_EQ(Expression("x / (5/6 I)").toString(),
            "-(6 I x)/5");
  EXPECT_EQ(Expression("x / (5/6 I + 2/7)").toString(),
            "((504 - 1470 I) x)/1369");
  EXPECT_EQ(Expression("x / (5/6 I + 2)").toString(),
            "((72 - 30 I) x)/169");
  EXPECT_EQ(Expression("x / (5 I + 2/7)").toString(),
            "((14 - 245 I) x)/1229");

  EXPECT_EQ(Expression("I = I").toString(),
            "True");
  EXPECT_EQ(Expression("I = 2 I").toString(),
            "False");
  EXPECT_EQ(Expression("I = I x").toString(),
            "x - 1 = 0");
  EXPECT_EQ(Expression("I x = I").toString(),
            "x - 1 = 0");

  EXPECT_EQ(Expression("I != I").toString(),
            "False");
  EXPECT_EQ(Expression("I != 2 I").toString(),
            "True");
  EXPECT_EQ(Expression("I != I x").toString(),
            "x - 1 != 0");
  EXPECT_EQ(Expression("I x != I").toString(),
            "x - 1 != 0");

  EXPECT_EQ(Expression("I < I").toString(),
            "I < I");
  EXPECT_EQ(Expression("I < 2 I").toString(),
            "I < 2 I");
  EXPECT_EQ(Expression("I < I x").toString(),
            "I < I x");
  EXPECT_EQ(Expression("I x < I").toString(),
            "I x < I");

  EXPECT_EQ(Expression("I > I").toString(),
            "I > I");
  EXPECT_EQ(Expression("I > 2 I").toString(),
            "I > 2 I");
  EXPECT_EQ(Expression("I x > I").toString(),
            "I x > I");

  EXPECT_EQ(Expression("I <= I").toString(),
            "I <= I");
  EXPECT_EQ(Expression("I <= 2 I").toString(),
            "I <= 2 I");
  EXPECT_EQ(Expression("I <= I x").toString(),
            "I <= I x");
  EXPECT_EQ(Expression("I x <= I").toString(),
            "I x <= I");

  EXPECT_EQ(Expression("I >= I").toString(),
            "I >= I");
  EXPECT_EQ(Expression("I >= 2 I").toString(),
            "I >= 2 I");
  EXPECT_EQ(Expression("I >= I x").toString(),
            "I >= I x");
  EXPECT_EQ(Expression("I x >= I").toString(),
            "I x >= I");

  EXPECT_EQ(Expression("2 I = E").toString(),
            "False");
  EXPECT_EQ(Expression("2 I > E").toString(),
            "2 I > E");
  EXPECT_EQ(Expression("E = 2 I").toString(),
            "False");
  EXPECT_EQ(Expression("E > 2 I").toString(),
            "E > 2 I");
  EXPECT_EQ(Expression("2 I + 3 = 0").toString(),
            "False");
  EXPECT_EQ(Expression("2 I + E > 0").toString(),
            "E + 2 I > 0");
}
