#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyComparisonsTests, simplifyTest) {
  EXPECT_EQ(Expression("a=a").toString(),
            "True");
  EXPECT_EQ(Expression("a+a=2*a").toString(),
            "True");
  EXPECT_EQ(Expression("a=b").toString(),
            "a - b = 0");
  EXPECT_EQ(Expression("a!=a").toString(),
            "False");
  EXPECT_EQ(Expression("a+a!=2*a").toString(),
            "False");
  EXPECT_EQ(Expression("a!=b").toString(),
            "a - b != 0");
  EXPECT_EQ(Expression("x<6").toString(),
            "x - 6 < 0");
  EXPECT_EQ(Expression("x<=6").toString(),
            "x - 6 <= 0");
  EXPECT_EQ(Expression("x>6").toString(),
            "x - 6 > 0");
  EXPECT_EQ(Expression("x>=6").toString(),
            "x - 6 >= 0");
  EXPECT_EQ(Expression("(5+5)=(2*5)").toString(),
            "True");
  EXPECT_EQ(Expression("((((5+5)=(2*5))))").toString(),
            "True");
  EXPECT_EQ(Expression("((1*1))(5+5)=((2*5)/(1/1))").toString(),
            "True");
  EXPECT_EQ(Expression("-x - 10 = 0").toString(),
            "x + 10 = 0");
  EXPECT_EQ(Expression("2x = 0").toString(),
            "x = 0");
  EXPECT_EQ(Expression("2x - 10 = 0").toString(),
            "x - 5 = 0");
  EXPECT_EQ(Expression("-a > 0").toString(),
            "a < 0");
  EXPECT_EQ(Expression("-2a + 5 > 6").toString(),
            "a + 1/2 < 0");
  EXPECT_EQ(Expression("-2a+5>6").toString(),
            "a + 1/2 < 0");
  EXPECT_EQ(Expression("-6x^2 + 4x - 20 = 15x - 9").toString(),
            "x^2 + (11 x)/6 + 11/6 = 0");
  EXPECT_EQ(Expression("2 a^5 b - 4 a b^5  = 0").toString(),
            "a^5 b - 2 a b^5 = 0");
  EXPECT_EQ(Expression("-2 a^5 b + 4 a b^5  = 0").toString(),
            "a^5 b - 2 a b^5 = 0");

  EXPECT_EQ(Expression("sin(E)=sin(E)").toString(),
            "True");
  EXPECT_EQ(Expression("sin(E)>sin(E)").toString(),
            "False");
  EXPECT_EQ(Expression("sin(E)>=sin(E)").toString(),
            "True");
  EXPECT_EQ(Expression("sin(E)<sin(E)").toString(),
            "False");
  EXPECT_EQ(Expression("sin(E)<=sin(E)").toString(),
            "True");
  EXPECT_EQ(Expression("log(E,5)=ln(5)").toString(),
            "True");
  EXPECT_EQ(Expression("log(E,5)<ln(5)").toString(),
            "False");
  EXPECT_EQ(Expression("log(E,5)>ln(5)").toString(),
            "False");
  EXPECT_EQ(Expression("log(E,5)<=ln(5)").toString(),
            "True");
  EXPECT_EQ(Expression("log(E,5)>=ln(5)").toString(),
            "True");
  EXPECT_EQ(Expression("log(1deg, (1deg)^(1deg)) = 1deg").toString(),
            "True");
  EXPECT_EQ(Expression("E^Pi > Pi^E").toString(),
            "True");
  EXPECT_EQ(Expression("Pi^E < E^Pi").toString(),
            "True");
  EXPECT_EQ(Expression("log(floor(E), E) = lb(E)").toString(),
            "True");

  EXPECT_EQ(Expression("I! > 0").toString(),
            "I! > 0");
  EXPECT_EQ(Expression("Inf mod 2 > 0").toString(),
            "Inf mod 2 > 0");
  EXPECT_EQ(Expression("Inf! - 1 = 0").toString(),
            "Inf! - 1 = 0");
  EXPECT_EQ(Expression("Inf - 1 > 0").toString(),
            "Inf > 0");
  EXPECT_EQ(Expression("Pi!! - Pi > 0").toString(),
            "Pi!! - Pi > 0");
}
