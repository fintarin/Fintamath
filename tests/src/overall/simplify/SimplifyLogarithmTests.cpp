#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyLogarithmTests, simplifyTest) {
  EXPECT_EQ(Expression("log(2, 2)").toString(),
            "1");
  EXPECT_EQ(Expression("log(2, 256)").toString(),
            "8");
  EXPECT_EQ(Expression("log(3, 515377520732011331036461129765621272702107522001)").toString(),
            "100");
  EXPECT_EQ(Expression("log(515377520732011331036461129765621272702107522001, 3)").toString(),
            "1/100");
  EXPECT_EQ(Expression("log(2/3, 4/9)").toString(),
            "2");
  EXPECT_EQ(Expression("log(9/4, 3/2)").toString(),
            "1/2");
  EXPECT_EQ(Expression("log(4/9, 2/3)").toString(),
            "1/2");
  EXPECT_EQ(Expression("log(4/11, 2/3)").toString(),
            "log(4/11, 2/3)");
  EXPECT_EQ(Expression("ln1").toString(),
            "0");
  EXPECT_EQ(Expression("ln3").toString(),
            "ln(3)");
  EXPECT_EQ(Expression("ln2").toString(),
            "ln(2)");
  EXPECT_EQ(Expression("ln100").toString(),
            "ln(100)");
  EXPECT_EQ(Expression("ln(E)").toString(),
            "1");
  EXPECT_EQ(Expression("lg99").toString(),
            "log(10, 99)");
  EXPECT_EQ(Expression("lg100").toString(),
            "2");
  EXPECT_EQ(Expression("lb100").toString(),
            "log(2, 100)");
  EXPECT_EQ(Expression("lb4").toString(),
            "2");
  EXPECT_EQ(Expression("ln(ln(E))").toString(),
            "0");
  EXPECT_EQ(Expression("ln(E)!").toString(),
            "1");
  EXPECT_EQ(Expression("log(0, 1)").toString(),
            "0");
  EXPECT_EQ(Expression("log(-1, 1)").toString(),
            "0");
  EXPECT_EQ(Expression("log(E,E)").toString(),
            "1");
  EXPECT_EQ(Expression("log(Pi, Pi^10)").toString(),
            "10");
  EXPECT_EQ(Expression("log(E,E^3)").toString(),
            "3");
  EXPECT_EQ(Expression("log((Pi),(E)^((Pi)))").toString(),
            "Pi log(Pi, E)");
  EXPECT_EQ(Expression("log(E^3, E)").toString(),
            "1/3");
  EXPECT_EQ(Expression("log(E^Pi, E)").toString(),
            "1/Pi");

  EXPECT_EQ(Expression("ln(x) + ln(y)").toString(),
            "ln(x y)");
  EXPECT_EQ(Expression("ln(x) - ln(y)").toString(),
            "ln(x/y)");
  EXPECT_EQ(Expression("-ln(x) + ln(y)").toString(),
            "ln(y/x)");
  EXPECT_EQ(Expression("-ln(x) - ln(y)").toString(),
            "ln(1/(x y))");
  EXPECT_EQ(Expression("lb(x)/y").toString(),
            "log(2, x)/y");
  EXPECT_EQ(Expression("ln((E)/(20000.1EE)) + ln(20000.1E)").toString(),
            "0");
  EXPECT_EQ(Expression("ln((10 E)^2) - ln(10 E 10 E)").toString(),
            "0");
  EXPECT_EQ(Expression("ln((10 E)^2) - 2 ln(10 E)").toString(),
            "0");
  EXPECT_EQ(Expression("3 ln((10 E)^2) - 2 ln(10 E)").toString(),
            "4 ln(10 E)");
  EXPECT_EQ(Expression("ln((10 E)^(2ab)) - 2 a ln(10 E) b").toString(),
            "0");
  EXPECT_EQ(Expression("ln((10 E)^(2 ln(2))) - 2 ln(2) ln(10 E)").toString(),
            "0");
  EXPECT_EQ(Expression("log(2.3, (E)/(20000.1*E*E)) + log(2.3, 20000.1*E)").toString(),
            "0");
  EXPECT_EQ(Expression("log(2.3, (E)/(20000.1*E*E)) - log(2.3, 20000.1*E)").toString(),
            "log(23/10, 100/(40000400001 E^2))");
  EXPECT_EQ(Expression("log(2, 3) + log(3, 4)").toString(),
            "log(3, 4) + log(2, 3)");
  EXPECT_EQ(Expression("x log(2, 3) + log(2, 5)").toString(),
            "log(2, 5*3^x)");
  EXPECT_EQ(Expression("x log(2, 3) + log(2, 5a)").toString(),
            "log(2, 5 a 3^x)");
  EXPECT_EQ(Expression("log(2, 3) + 3log(3, 4)").toString(),
            "log(2, 3) + 3 log(3, 4)");
  EXPECT_EQ(Expression("3log(2x, 3) + log(3, 4)").toString(),
            "3 log(2 x, 3) + log(3, 4)");
  EXPECT_EQ(Expression("3log(2x, 3) + 4log(3, 4)").toString(),
            "3 log(2 x, 3) + 4 log(3, 4)");
  EXPECT_EQ(Expression("3log(2x, 3) + 5log(2x, 4)").toString(),
            "log(2 x, 27648)");
}
