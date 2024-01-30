#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyDivisionTests, simplifyTest) {
  EXPECT_EQ(Expression("-9 / (3x+3)").toString(),
            "-3/(x + 1)");
  EXPECT_EQ(Expression("(4x^2 - 5x - 21) / (x - 3)").toString(),
            "4 x + 7");
  EXPECT_EQ(Expression("(3x^3 - 5x^2 + 10x - 3) / (3x + 1)").toString(),
            "x^2 - 2 x + 4 - 7/(3 x + 1)");
  EXPECT_EQ(Expression("(2x^3 - 9x^2 + 15) / (2x - 5)").toString(),
            "x^2 - 2 x - 5 - 10/(2 x - 5)");
  EXPECT_EQ(Expression("(4x^4 + 1 + 3x^3 + 2x) / (x^2 + x + 2)").toString(),
            "4 x^2 - x - 7 + (11 x + 15)/(x^2 + x + 2)");
  EXPECT_EQ(Expression("(2x^4 - 3x^3 + 4x^2 - 5x + 6) / (x^2 + 2x - 3)").toString(),
            "2 x^2 - 7 x + 24 - (74 x - 78)/(x^2 + 2 x - 3)");
  EXPECT_EQ(Expression("(4x^5 + 2x^4 - 6x^3 + 3x^2 + x - 2) / (2x^3 + x^2 - 3x + 2)").toString(),
            "2 x^2 - (x^2 - x + 2)/(2 x^3 + x^2 - 3 x + 2)");
  EXPECT_EQ(Expression("(3x^6 + 5x^5 - 2x^4 + 4x^3 + x^2 + 3x - 5) / (x^4 + 3x^2 - 2)").toString(),
            "3 x^2 + 5 x - 11 - (11 x^3 - 40 x^2 - 13 x + 27)/(x^4 + 3 x^2 - 2)");
  EXPECT_EQ(Expression("(6x^8 - 7x^6 + 9x^4 - 4x^2 + 8) / (2x^3 - x^2 + 3x - 1)").toString(),
            "3 x^5 + (3 x^4)/2 - (29 x^3)/4 - (35 x^2)/8 + (223 x)/16 + 317/32 - (1289 x^2 + 505 x - 573)/(64 x^3 - 32 x^2 + 96 x - 32)");
  EXPECT_EQ(Expression("(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)/(25 a^2 + 40 a b + 15 b^2)").toString(),
            "(2 a)/25 + (9 b)/125 - (2 a b^2 + 2 b^3)/(625 a^2 + 1000 a b + 375 b^2)");
  EXPECT_EQ(Expression("(25 a^2 + 40 a b + 15 b^2)/(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)").toString(),
            "(25 a^2 + 40 a b + 15 b^2)/(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)");
  EXPECT_EQ(Expression("(x^2 + 2x + 1)/(x^3 + 3x^2 + 3x + 1)").toString(),
            "1/(x + 1)");
  EXPECT_EQ(Expression("5/(a+b) + 5/(2a+b) + 5/(a+b)").toString(),
            "(25 a^2 + 40 a b + 15 b^2)/(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)");
  EXPECT_EQ(Expression("(x+y)/(a+b) + 5/(2a+b) + (x+2y)/(a+b)").toString(),
            "(4 a^2 x + 6 a^2 y + 5 a^2 + 6 a b x + 9 a b y + 10 a b + 2 b^2 x + 3 b^2 y + 5 b^2)/(2 a^3 + 5 a^2 b + 4 a b^2 + b^3)"); // TODO: "(4 a x + 6 a y + 5 a + 2 b x + 3 b y + 5 b)/(2 a^2 + 3 a b + b^2)"
  EXPECT_EQ(Expression("(a/b)(c/d)").toString(),
            "(a c)/(b d)");
  EXPECT_EQ(Expression("(ab/2)(ad/3)").toString(),
            "(a^2 b d)/6");
  EXPECT_EQ(Expression("(-a)(-b)").toString(),
            "a b");
  EXPECT_EQ(Expression("(a)(-b)").toString(),
            "-a b");
  EXPECT_EQ(Expression("(-a)(b)").toString(),
            "-a b");
  EXPECT_EQ(Expression("(5/3 b)/a").toString(),
            "(5 b)/(3 a)");
  EXPECT_EQ(Expression("(5/3 + b)/(2/5 + a)").toString(),
            "(15 b + 25)/(15 a + 6)");
  EXPECT_EQ(Expression("(a b)/(a b)").toString(),
            "1");
  EXPECT_EQ(Expression("(a b)/1").toString(),
            "a b");
  EXPECT_EQ(Expression("(a b)/-1").toString(),
            "-a b");
  EXPECT_EQ(Expression("(a b)/-2").toString(),
            "-(a b)/2");
  EXPECT_EQ(Expression("(a b)/(-a - b)").toString(),
            "-b + (b^2)/(a + b)");
  EXPECT_EQ(Expression("(x^5)/(x - y)").toString(),
            "x^4 + x^3 y + x^2 y^2 + x y^3 + y^4 + (y^5)/(x - y)");
  EXPECT_EQ(Expression("(3 x + 5/9)/(2y - 9/x + 3/2 x + 1/2 + 2 y / x)").toString(),
            "2 - (72 x^2 y + 8 x^2 + 72 x y - 324 x)/(27 x^3 + 36 x^2 y + 9 x^2 + 36 x y - 162 x)"); // TODO: "2 - (72 x y + 8 x + 72 y - 324)/(27 x^2 + 36 x y + 9 x + 36 y - 162)"
  EXPECT_EQ(Expression("(a/x + b/(y+3/r)/4)/(3+t/5)").toString(),
            "(20 a r y + 60 a + 5 b r x)/(4 r t x y + 60 r x y + 12 t x + 180 x)");
  EXPECT_EQ(Expression("(x/a - (b+5)/(y-8/(12 y))/4)/(8-a/5)").toString(),
            "(15 a b y + 75 a y - 60 x y^2 + 40 x)/(12 a^2 y^2 - 8 a^2 - 480 a y^2 + 320 a)");
  EXPECT_EQ(Expression("(a + b + c^2) / ((a + b + c^3) / (5/2 * (a + b) / (3/b + c/2)))").toString(),
            "5 c + (5 a^2 b + 10 a b^2 - 30 a c + 5 b^3 - 5 b c^5 - 30 b c - 30 c^4)/(a b c + 6 a + b^2 c + b c^4 + 6 "
            "b + 6 c^3)");
  EXPECT_EQ(Expression("((2xy)/(x^2 - y^2) + (x - y)/(2x + 2y)) * (2x)/(x + y) + y/(y - x)").toString(),
            "1");
  EXPECT_EQ(Expression("y/(x - y) - (x ^3 - xy ^2)/(x ^2 + y ^2) * (x/((x - y) ^2) - y/(x ^2 - y ^2))").toString(),
            "-1");
  EXPECT_EQ(Expression("(a+3)/(b+2)").toString(),
            "(a + 3)/(b + 2)");
  EXPECT_EQ(Expression("b/a*(a+3)/(b+2)").toString(),
            "1 - (2 a - 3 b)/(a b + 2 a)");
  EXPECT_EQ(Expression("(5+b)/a*(a+3)/(b+2)").toString(),
            "1 + (3 a + 3 b + 15)/(a b + 2 a)");
  EXPECT_EQ(Expression("(a+b)*(a+b)/(a+b)").toString(),
            "a + b");
  EXPECT_EQ(Expression("(a+b)*(a+b)*(1/(a+b))").toString(),
            "a + b");
  EXPECT_EQ(Expression("(x^2+2x+1)/(x+1)").toString(),
            "x + 1");
  EXPECT_EQ(Expression("(1/2 + sqrt(3)) / (x^(1/4) + 6)").toString(),
            "(2 sqrt(3) + 1)/(2 root(x, 4) + 12)");
  EXPECT_EQ(Expression("(x^2 + sqrt(y) - 45) / (sqrt(3) + 3)").toString(),
            "(x^2 + sqrt(y) - 45)/(sqrt(3) + 3)");
  EXPECT_EQ(Expression("(x^2 + sqrt(y) - 45x) / (root(3, 4) + 3)").toString(),
            "(x^2 - 45 x + sqrt(y))/(root(3, 4) + 3)");
  EXPECT_EQ(Expression("(x^2 + sqrt(y) - 45x) / (root(3, 4) x + 3)").toString(),
            "(root(27, 4) x)/3 - sqrt(3) - 15 root(27, 4) + (sqrt(y) + 45 root(27, 4) + 3 sqrt(3))/(root(3, 4) x + 3)");
  EXPECT_EQ(Expression("(sqrt(-4 a c + b^2) - b) / (2 a)").toString(),
            "(sqrt(-4 a c + b^2) - b)/(2 a)");
}
