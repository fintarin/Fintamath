#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyTrigonometryTests, simplifyTest) {
  EXPECT_EQ(Expression("sin(asin(x))").toString(),
            "x");
  EXPECT_EQ(Expression("cos(acos(x))").toString(),
            "x");
  EXPECT_EQ(Expression("tan(atan(x))").toString(),
            "x");
  EXPECT_EQ(Expression("cot(acot(x))").toString(),
            "x");
  EXPECT_EQ(Expression("sec(asec(x))").toString(),
            "x");
  EXPECT_EQ(Expression("csc(acsc(x))").toString(),
            "x");
  EXPECT_EQ(Expression("asin(sin(x))").toString(),
            "asin(sin(x))");
  EXPECT_EQ(Expression("acos(cos(x))").toString(),
            "acos(cos(x))");
  EXPECT_EQ(Expression("atan(tan(x))").toString(),
            "atan(tan(x))");
  EXPECT_EQ(Expression("acot(cot(x))").toString(),
            "acot(cot(x))");
  EXPECT_EQ(Expression("asec(sec(x))").toString(),
            "asec(sec(x))");
  EXPECT_EQ(Expression("acsc(csc(x))").toString(),
            "acsc(csc(x))");

  EXPECT_EQ(Expression("sin(-x)").toString(),
            "-sin(x)");
  EXPECT_EQ(Expression("cos(-x)").toString(),
            "cos(x)");
  EXPECT_EQ(Expression("tan(-x)").toString(),
            "-tan(x)");
  EXPECT_EQ(Expression("cot(-x)").toString(),
            "-cot(x)");
  EXPECT_EQ(Expression("sec(-x)").toString(),
            "sec(x)");
  EXPECT_EQ(Expression("csc(-x)").toString(),
            "-csc(x)");

  EXPECT_EQ(Expression("sin(x)/cos(x)").toString(),
            "tan(x)");
  EXPECT_EQ(Expression("(-2sin(x))/cos(x)").toString(),
            "-2 tan(x)");
  EXPECT_EQ(Expression("(2sin(x))/(3cos(x))").toString(),
            "(2 tan(x))/3");
  EXPECT_EQ(Expression("sin(x)^2/cos(x)").toString(),
            "sin(x)^2 sec(x)");
  EXPECT_EQ(Expression("sin(x)/cos(x)^2").toString(),
            "sec(x)^2 sin(x)");
  EXPECT_EQ(Expression("sin(x)^2/cos(x)^2").toString(),
            "tan(x)^2");
  EXPECT_EQ(Expression("(2sin(x))^2/cos(x)^2").toString(),
            "4 tan(x)^2");
  EXPECT_EQ(Expression("(2sin(x))^2/(3cos(x))^2").toString(),
            "(4 tan(x)^2)/9");

  EXPECT_EQ(Expression("cos(x)/sin(x)").toString(),
            "cot(x)");
  EXPECT_EQ(Expression("(-2cos(x))/sin(x)").toString(),
            "-2 cot(x)");
  EXPECT_EQ(Expression("(2cos(x))/(3sin(x))").toString(),
            "(2 cot(x))/3");
  EXPECT_EQ(Expression("cos(x)^2/sin(x)").toString(),
            "cos(x)^2 csc(x)");
  EXPECT_EQ(Expression("cos(x)/sin(x)^2").toString(),
            "csc(x)^2 cos(x)");
  EXPECT_EQ(Expression("cos(x)^2/sin(x)^2").toString(),
            "cot(x)^2");
  EXPECT_EQ(Expression("(2cos(x))^2/sin(x)^2").toString(),
            "4 cot(x)^2");
  EXPECT_EQ(Expression("(2cos(x))^2/(3sin(x))^2").toString(),
            "(4 cot(x)^2)/9");

  EXPECT_EQ(Expression("sec(x)/csc(x)").toString(),
            "tan(x)");
  EXPECT_EQ(Expression("csc(x)/sec(x)").toString(),
            "cot(x)");
  EXPECT_EQ(Expression("sec(x)*cot(x)").toString(),
            "csc(x)");
  EXPECT_EQ(Expression("csc(x)*tan(x)").toString(),
            "sec(x)");

  EXPECT_EQ(Expression("sin(x)cos(x)").toString(),
            "sin(2 x)/2");
  EXPECT_EQ(Expression("sin(x)cos(x)sign(x)").toString(),
            "(sin(2 x) sign(x))/2");

  EXPECT_EQ(Expression("sin(x)^2").toString(),
            "sin(x)^2");
  EXPECT_EQ(Expression("cos(x)^2").toString(),
            "cos(x)^2");
  EXPECT_EQ(Expression("1 - sin(x)^2").toString(),
            "cos(x)^2");
  EXPECT_EQ(Expression("-1 + sin(x)^2").toString(),
            "-cos(x)^2");
  EXPECT_EQ(Expression("2 - 2sin(x)^2").toString(),
            "2 cos(x)^2");
  EXPECT_EQ(Expression("-2 + 2sin(x)^2").toString(),
            "-2 cos(x)^2");
  EXPECT_EQ(Expression("1 - cos(x)^2").toString(),
            "sin(x)^2");
  EXPECT_EQ(Expression("-1 + cos(x)^2").toString(),
            "-sin(x)^2");
  EXPECT_EQ(Expression("2 - 2cos(x)^2").toString(),
            "2 sin(x)^2");
  EXPECT_EQ(Expression("-2 + 2cos(x)^2").toString(),
            "-2 sin(x)^2");
  EXPECT_EQ(Expression("1 - 2sin(x)^2").toString(),
            "-2 sin(x)^2 + 1"); // TODO: cos of double angle
  EXPECT_EQ(Expression("1 - 2cos(x)^2").toString(),
            "-2 cos(x)^2 + 1"); // TODO: cos of double angle

  EXPECT_EQ(Expression("sin(x)^2 + cos(x)^2").toString(),
            "1");
  EXPECT_EQ(Expression("sin(x)^2 - cos(x)^2").toString(),
            "-cos(2 x)");
  EXPECT_EQ(Expression("-sin(x)^2 + cos(x)^2").toString(),
            "cos(2 x)");
  EXPECT_EQ(Expression("-sin(x)^2 - cos(x)^2").toString(),
            "-1");
  EXPECT_EQ(Expression("2sin(x)^2 + 2cos(x)^2").toString(),
            "2");
  EXPECT_EQ(Expression("sin(x)^2 + 2cos(x)^2").toString(),
            "sin(x)^2 + 2 cos(x)^2");
  EXPECT_EQ(Expression("2sin(x)^2 + cos(x)^2").toString(),
            "2 sin(x)^2 + cos(x)^2");
  EXPECT_EQ(Expression("2sin(x)^2 - 3cos(x)^2").toString(),
            "2 sin(x)^2 - 3 cos(x)^2");
  EXPECT_EQ(Expression("-5sin(x)^2 + 10cos(x)^2").toString(),
            "-5 sin(x)^2 + 10 cos(x)^2");
  EXPECT_EQ(Expression("-4sin(x)^2 - 6cos(x)^2").toString(),
            "-4 sin(x)^2 - 6 cos(x)^2");
  EXPECT_EQ(Expression("(2I + 2) sin(x)^2 + (2I + 2) cos(x)^2").toString(),
            "2 + 2 I");
  EXPECT_EQ(Expression("(2I + 2) sin(x)^2 + (2I - 2) cos(x)^2").toString(),
            "(2 + 2 I) sin(x)^2 + (-2 + 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(2I + 2) sin(x)^2 + (-2I + 2) cos(x)^2").toString(),
            "(2 + 2 I) sin(x)^2 + (2 - 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(2I + 2) sin(x)^2 + (-2I - 2) cos(x)^2").toString(),
            "(-2 - 2 I) cos(2 x)");
  EXPECT_EQ(Expression("(2I - 2) sin(x)^2 + (2I + 2) cos(x)^2").toString(),
            "(-2 + 2 I) sin(x)^2 + (2 + 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(2I - 2) sin(x)^2 + (2I - 2) cos(x)^2").toString(),
            "-2 + 2 I");
  EXPECT_EQ(Expression("(2I - 2) sin(x)^2 + (-2I + 2) cos(x)^2").toString(),
            "(2 - 2 I) cos(2 x)");
  EXPECT_EQ(Expression("(2I - 2) sin(x)^2 + (-2I - 2) cos(x)^2").toString(),
            "(-2 + 2 I) sin(x)^2 + (-2 - 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(-2I + 2) sin(x)^2 + (2I + 2) cos(x)^2").toString(),
            "(2 - 2 I) sin(x)^2 + (2 + 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(-2I + 2) sin(x)^2 + (2I - 2) cos(x)^2").toString(),
            "(-2 + 2 I) cos(2 x)");
  EXPECT_EQ(Expression("(-2I + 2) sin(x)^2 + (-2I + 2) cos(x)^2").toString(),
            "2 - 2 I");
  EXPECT_EQ(Expression("(-2I + 2) sin(x)^2 + (-2I - 2) cos(x)^2").toString(),
            "(2 - 2 I) sin(x)^2 + (-2 - 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(-2I - 2) sin(x)^2 + (2I + 2) cos(x)^2").toString(),
            "(2 + 2 I) cos(2 x)");
  EXPECT_EQ(Expression("(-2I - 2) sin(x)^2 + (2I - 2) cos(x)^2").toString(),
            "(-2 - 2 I) sin(x)^2 + (-2 + 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(-2I - 2) sin(x)^2 + (-2I + 2) cos(x)^2").toString(),
            "(-2 - 2 I) sin(x)^2 + (2 - 2 I) cos(x)^2");
  EXPECT_EQ(Expression("(-2I - 2) sin(x)^2 + (-2I - 2) cos(x)^2").toString(),
            "-2 - 2 I");
  // TODO: simplify
  EXPECT_EQ(Expression("E sin(x)^2 + E cos(x)^2").toString(),
            "E sin(x)^2 + E cos(x)^2");
  EXPECT_EQ(Expression("E sin(x)^2 - E cos(x)^2").toString(),
            "E sin(x)^2 - E cos(x)^2");
  EXPECT_EQ(Expression("-E sin(x)^2 + E cos(x)^2").toString(),
            "-E sin(x)^2 + E cos(x)^2");
  EXPECT_EQ(Expression("-E sin(x)^2 - E cos(x)^2").toString(),
            "-E sin(x)^2 - E cos(x)^2");
  EXPECT_EQ(Expression("E^2 sin(x)^2 + E cos(x)^2").toString(),
            "sin(x)^2 E^2 + E cos(x)^2");
  EXPECT_EQ(Expression("E^2 sin(x)^2 - E cos(x)^2").toString(),
            "sin(x)^2 E^2 - E cos(x)^2");
  EXPECT_EQ(Expression("-E^2 sin(x)^2 + E cos(x)^2").toString(),
            "-sin(x)^2 E^2 + E cos(x)^2");
  EXPECT_EQ(Expression("-E^2 sin(x)^2 - E cos(x)^2").toString(),
            "-sin(x)^2 E^2 - E cos(x)^2");
  EXPECT_EQ(Expression("sin(x) * sin(x) + cos(x) * cos(x)").toString(),
            "1");
  EXPECT_EQ(Expression("(sin(x) + cos(x))^2").toString(),
            "sin(2 x) + 1");
  EXPECT_EQ(Expression("(sin(x) - cos(x))^2").toString(),
            "-sin(2 x) + 1");
  EXPECT_EQ(Expression("sin(x)^2 + cos(y)^2").toString(),
            "sin(x)^2 + cos(y)^2");

  EXPECT_EQ(Expression("sin(x)^2 + sign(x)^2").toString(),
            "sin(x)^2 + sign(x)^2");
  EXPECT_EQ(Expression("sin(x)^2 - sign(x)^2").toString(),
            "sin(x)^2 - sign(x)^2");
  EXPECT_EQ(Expression("cos(x)^2 + sign(x)^2").toString(),
            "cos(x)^2 + sign(x)^2");
  EXPECT_EQ(Expression("cos(x)^2 - sign(x)^2").toString(),
            "cos(x)^2 - sign(x)^2");
  EXPECT_EQ(Expression("sign(x)^2 + 1").toString(),
            "sign(x)^2 + 1");
  EXPECT_EQ(Expression("sign(x)^2 - 1").toString(),
            "sign(x)^2 - 1");

  EXPECT_EQ(Expression("tan(x) * cot(x)").toString(),
            "1");
  EXPECT_EQ(Expression("cot(x) * tan(x)").toString(),
            "1");
  EXPECT_EQ(Expression("sec(x) * cos(x)").toString(),
            "1");
  EXPECT_EQ(Expression("cos(x) * sec(x)").toString(),
            "1");
  EXPECT_EQ(Expression("csc(x) * sin(x)").toString(),
            "1");
  EXPECT_EQ(Expression("sin(x) * csc(x)").toString(),
            "1");
  // TODO: implement
  // EXPECT_EQ(Expression("tan(x)^5 * cot(x)^5").toString(),
  //           "1");
  // EXPECT_EQ(Expression("tan(x)^4 * (sin(x)/cos(x)) * cot(x)^5").toString(),
  //           "1");

  EXPECT_EQ(Expression("sin(-13Pi/6)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("sin(-2Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("sin(-11Pi/6)").toString(),
            "1/2");
  EXPECT_EQ(Expression("sin(-7Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("sin(-5Pi/3)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("sin(-3Pi/2)").toString(),
            "1");
  EXPECT_EQ(Expression("sin(-4Pi/3)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("sin(-5Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("sin(-7Pi/6)").toString(),
            "1/2");
  EXPECT_EQ(Expression("sin(-Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("sin(-5Pi/6)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("sin(-3Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("sin(-2Pi/3)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("sin(-Pi/2)").toString(),
            "-1");
  EXPECT_EQ(Expression("sin(-Pi/3)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("sin(-Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("sin(-Pi/6)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("sin(0)").toString(),
            "0");
  EXPECT_EQ(Expression("sin(Pi/6)").toString(),
            "1/2");
  EXPECT_EQ(Expression("sin(Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("sin(Pi/3)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("sin(Pi/2)").toString(),
            "1");
  EXPECT_EQ(Expression("sin(2Pi/3)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("sin(3Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("sin(5Pi/6)").toString(),
            "1/2");
  EXPECT_EQ(Expression("sin(Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("sin(7Pi/6)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("sin(5Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("sin(4Pi/3)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("sin(3Pi/2)").toString(),
            "-1");
  EXPECT_EQ(Expression("sin(5Pi/3)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("sin(7Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("sin(11Pi/6)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("sin(2Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("sin(13Pi/6)").toString(),
            "1/2");

  EXPECT_EQ(Expression("cos(-13Pi/6)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("cos(-2Pi)").toString(),
            "1");
  EXPECT_EQ(Expression("cos(-11Pi/6)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("cos(-7Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("cos(-5Pi/3)").toString(),
            "1/2");
  EXPECT_EQ(Expression("cos(-3Pi/2)").toString(),
            "0");
  EXPECT_EQ(Expression("cos(-4Pi/3)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("cos(-5Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("cos(-7Pi/6)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("cos(-Pi)").toString(),
            "-1");
  EXPECT_EQ(Expression("cos(-5Pi/6)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("cos(-3Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("cos(-2Pi/3)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("cos(-Pi/2)").toString(),
            "0");
  EXPECT_EQ(Expression("cos(-Pi/3)").toString(),
            "1/2");
  EXPECT_EQ(Expression("cos(-Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("cos(-Pi/6)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("cos(0)").toString(),
            "1");
  EXPECT_EQ(Expression("cos(Pi/6)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("cos(Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("cos(Pi/3)").toString(),
            "1/2");
  EXPECT_EQ(Expression("cos(Pi/2)").toString(),
            "0");
  EXPECT_EQ(Expression("cos(2Pi/3)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("cos(3Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("cos(5Pi/6)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("cos(Pi)").toString(),
            "-1");
  EXPECT_EQ(Expression("cos(7Pi/6)").toString(),
            "-sqrt(3)/2");
  EXPECT_EQ(Expression("cos(5Pi/4)").toString(),
            "-sqrt(2)/2");
  EXPECT_EQ(Expression("cos(4Pi/3)").toString(),
            "-1/2");
  EXPECT_EQ(Expression("cos(3Pi/2)").toString(),
            "0");
  EXPECT_EQ(Expression("cos(5Pi/3)").toString(),
            "1/2");
  EXPECT_EQ(Expression("cos(7Pi/4)").toString(),
            "sqrt(2)/2");
  EXPECT_EQ(Expression("cos(11Pi/6)").toString(),
            "sqrt(3)/2");
  EXPECT_EQ(Expression("cos(2Pi)").toString(),
            "1");
  EXPECT_EQ(Expression("cos(13Pi/6)").toString(),
            "sqrt(3)/2");

  EXPECT_EQ(Expression("tan(-13Pi/6)").toString(),
            "-sqrt(3)/3");
  EXPECT_EQ(Expression("tan(-2Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("tan(-11Pi/6)").toString(),
            "sqrt(3)/3");
  EXPECT_EQ(Expression("tan(-7Pi/4)").toString(),
            "1");
  EXPECT_EQ(Expression("tan(-5Pi/3)").toString(),
            "sqrt(3)");
  EXPECT_EQ(Expression("tan(-3Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("tan(-4Pi/3)").toString(),
            "-sqrt(3)");
  EXPECT_EQ(Expression("tan(-5Pi/4)").toString(),
            "-1");
  EXPECT_EQ(Expression("tan(-7Pi/6)").toString(),
            "-sqrt(3)/3");
  EXPECT_EQ(Expression("tan(-Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("tan(-5Pi/6)").toString(),
            "sqrt(3)/3");
  EXPECT_EQ(Expression("tan(-3Pi/4)").toString(),
            "1");
  EXPECT_EQ(Expression("tan(-2Pi/3)").toString(),
            "sqrt(3)");
  EXPECT_EQ(Expression("tan(-Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("tan(-Pi/3)").toString(),
            "-sqrt(3)");
  EXPECT_EQ(Expression("tan(-Pi/4)").toString(),
            "-1");
  EXPECT_EQ(Expression("tan(-Pi/6)").toString(),
            "-sqrt(3)/3");
  EXPECT_EQ(Expression("tan(0)").toString(),
            "0");
  EXPECT_EQ(Expression("tan(Pi/6)").toString(),
            "sqrt(3)/3");
  EXPECT_EQ(Expression("tan(Pi/4)").toString(),
            "1");
  EXPECT_EQ(Expression("tan(Pi/3)").toString(),
            "sqrt(3)");
  EXPECT_EQ(Expression("tan(Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("tan(2Pi/3)").toString(),
            "-sqrt(3)");
  EXPECT_EQ(Expression("tan(3Pi/4)").toString(),
            "-1");
  EXPECT_EQ(Expression("tan(5Pi/6)").toString(),
            "-sqrt(3)/3");
  EXPECT_EQ(Expression("tan(Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("tan(7Pi/6)").toString(),
            "sqrt(3)/3");
  EXPECT_EQ(Expression("tan(5Pi/4)").toString(),
            "1");
  EXPECT_EQ(Expression("tan(4Pi/3)").toString(),
            "sqrt(3)");
  EXPECT_EQ(Expression("tan(3Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("tan(5Pi/3)").toString(),
            "-sqrt(3)");
  EXPECT_EQ(Expression("tan(7Pi/4)").toString(),
            "-1");
  EXPECT_EQ(Expression("tan(11Pi/6)").toString(),
            "-sqrt(3)/3");
  EXPECT_EQ(Expression("tan(2Pi)").toString(),
            "0");
  EXPECT_EQ(Expression("tan(13Pi/6)").toString(),
            "sqrt(3)/3");

  EXPECT_EQ(Expression("sec(-13Pi/6)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(-2Pi)").toString(),
            "1");
  EXPECT_EQ(Expression("sec(-11Pi/6)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(-7Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("sec(-5Pi/3)").toString(),
            "2");
  EXPECT_EQ(Expression("sec(-3Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("sec(-4Pi/3)").toString(),
            "-2");
  EXPECT_EQ(Expression("sec(-5Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("sec(-7Pi/6)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(-Pi)").toString(),
            "-1");
  EXPECT_EQ(Expression("sec(-5Pi/6)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(-3Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("sec(-2Pi/3)").toString(),
            "-2");
  EXPECT_EQ(Expression("sec(-Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("sec(-Pi/3)").toString(),
            "2");
  EXPECT_EQ(Expression("sec(-Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("sec(-Pi/6)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(0)").toString(),
            "1");
  EXPECT_EQ(Expression("sec(Pi/6)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("sec(Pi/3)").toString(),
            "2");
  EXPECT_EQ(Expression("sec(Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("sec(2Pi/3)").toString(),
            "-2");
  EXPECT_EQ(Expression("sec(3Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("sec(5Pi/6)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(Pi)").toString(),
            "-1");
  EXPECT_EQ(Expression("sec(7Pi/6)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(5Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("sec(4Pi/3)").toString(),
            "-2");
  EXPECT_EQ(Expression("sec(3Pi/2)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("sec(5Pi/3)").toString(),
            "2");
  EXPECT_EQ(Expression("sec(7Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("sec(11Pi/6)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("sec(2Pi)").toString(),
            "1");
  EXPECT_EQ(Expression("sec(13Pi/6)").toString(),
            "(2 sqrt(3))/3");

  EXPECT_EQ(Expression("csc(-13Pi/6)").toString(),
            "-2");
  EXPECT_EQ(Expression("csc(-2Pi)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("csc(-11Pi/6)").toString(),
            "2");
  EXPECT_EQ(Expression("csc(-7Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("csc(-5Pi/3)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(-3Pi/2)").toString(),
            "1");
  EXPECT_EQ(Expression("csc(-4Pi/3)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(-5Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("csc(-7Pi/6)").toString(),
            "2");
  EXPECT_EQ(Expression("csc(-Pi)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("csc(-5Pi/6)").toString(),
            "-2");
  EXPECT_EQ(Expression("csc(-3Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("csc(-2Pi/3)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(-Pi/2)").toString(),
            "-1");
  EXPECT_EQ(Expression("csc(-Pi/3)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(-Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("csc(-Pi/6)").toString(),
            "-2");
  EXPECT_EQ(Expression("csc(0)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("csc(Pi/6)").toString(),
            "2");
  EXPECT_EQ(Expression("csc(Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("csc(Pi/3)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(Pi/2)").toString(),
            "1");
  EXPECT_EQ(Expression("csc(2Pi/3)").toString(),
            "(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(3Pi/4)").toString(),
            "sqrt(2)");
  EXPECT_EQ(Expression("csc(5Pi/6)").toString(),
            "2");
  EXPECT_EQ(Expression("csc(Pi)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("csc(7Pi/6)").toString(),
            "-2");
  EXPECT_EQ(Expression("csc(5Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("csc(4Pi/3)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(3Pi/2)").toString(),
            "-1");
  EXPECT_EQ(Expression("csc(5Pi/3)").toString(),
            "-(2 sqrt(3))/3");
  EXPECT_EQ(Expression("csc(7Pi/4)").toString(),
            "-sqrt(2)");
  EXPECT_EQ(Expression("csc(11Pi/6)").toString(),
            "-2");
  EXPECT_EQ(Expression("csc(2Pi)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("csc(13Pi/6)").toString(),
            "2");

  EXPECT_EQ(Expression("sin(Pi/7)").toString(),
            "sin(Pi/7)");
  EXPECT_EQ(Expression("cos(Pi/7)").toString(),
            "cos(Pi/7)");
  EXPECT_EQ(Expression("tan(Pi/7)").toString(),
            "tan(Pi/7)");
  EXPECT_EQ(Expression("cot(Pi/7)").toString(),
            "cot(Pi/7)");
  EXPECT_EQ(Expression("sec(Pi/7)").toString(),
            "sec(Pi/7)");
  EXPECT_EQ(Expression("csc(Pi/7)").toString(),
            "csc(Pi/7)");

  EXPECT_EQ(Expression("sin(E Pi)").toString(),
            "sin(E Pi)");
  EXPECT_EQ(Expression("cos(E Pi)").toString(),
            "cos(E Pi)");
  EXPECT_EQ(Expression("tan(E Pi)").toString(),
            "tan(E Pi)");
  EXPECT_EQ(Expression("cot(E Pi)").toString(),
            "cot(E Pi)");
  EXPECT_EQ(Expression("sec(E Pi)").toString(),
            "sec(E Pi)");
  EXPECT_EQ(Expression("csc(E Pi)").toString(),
            "csc(E Pi)");

  EXPECT_EQ(Expression("asin(-1)").toString(),
            "-Pi/2");
  EXPECT_EQ(Expression("asin(-sqrt(3)/2)").toString(),
            "-Pi/3");
  EXPECT_EQ(Expression("asin(-sqrt(2)/2)").toString(),
            "-Pi/4");
  EXPECT_EQ(Expression("asin(-1/2)").toString(),
            "-Pi/6");
  EXPECT_EQ(Expression("asin(0)").toString(),
            "0");
  EXPECT_EQ(Expression("asin(1/2)").toString(),
            "Pi/6");
  EXPECT_EQ(Expression("asin(sqrt(2)/2)").toString(),
            "Pi/4");
  EXPECT_EQ(Expression("asin(sqrt(3)/2)").toString(),
            "Pi/3");
  EXPECT_EQ(Expression("asin(1)").toString(),
            "Pi/2");

  EXPECT_EQ(Expression("acos(-1)").toString(),
            "Pi");
  EXPECT_EQ(Expression("acos(-sqrt(3)/2)").toString(),
            "(5 Pi)/6");
  EXPECT_EQ(Expression("acos(-sqrt(2)/2)").toString(),
            "(3 Pi)/4");
  EXPECT_EQ(Expression("acos(-1/2)").toString(),
            "(2 Pi)/3");
  EXPECT_EQ(Expression("acos(0)").toString(),
            "Pi/2");
  EXPECT_EQ(Expression("acos(1/2)").toString(),
            "Pi/3");
  EXPECT_EQ(Expression("acos(sqrt(2)/2)").toString(),
            "Pi/4");
  EXPECT_EQ(Expression("acos(sqrt(3)/2)").toString(),
            "Pi/6");
  EXPECT_EQ(Expression("acos(1)").toString(),
            "0");

  EXPECT_EQ(Expression("atan(-sqrt(3))").toString(),
            "-Pi/3");
  EXPECT_EQ(Expression("atan(-1)").toString(),
            "-Pi/4");
  EXPECT_EQ(Expression("atan(-sqrt(3)/3)").toString(),
            "-Pi/6");
  EXPECT_EQ(Expression("atan(0)").toString(),
            "0");
  EXPECT_EQ(Expression("atan(sqrt(3)/3)").toString(),
            "Pi/6");
  EXPECT_EQ(Expression("atan(1)").toString(),
            "Pi/4");
  EXPECT_EQ(Expression("atan(sqrt(3))").toString(),
            "Pi/3");

  EXPECT_EQ(Expression("acot(-sqrt(3))").toString(),
            "-Pi/6");
  EXPECT_EQ(Expression("acot(-1)").toString(),
            "-Pi/4");
  EXPECT_EQ(Expression("acot(-sqrt(3)/3)").toString(),
            "-Pi/3");
  EXPECT_EQ(Expression("acot(0)").toString(),
            "Pi/2");
  EXPECT_EQ(Expression("acot(sqrt(3)/3)").toString(),
            "Pi/3");
  EXPECT_EQ(Expression("acot(1)").toString(),
            "Pi/4");
  EXPECT_EQ(Expression("acot(sqrt(3))").toString(),
            "Pi/6");

  EXPECT_EQ(Expression("asec(-1)").toString(),
            "Pi");
  EXPECT_EQ(Expression("asec(-2/sqrt(3))").toString(),
            "(5 Pi)/6");
  EXPECT_EQ(Expression("asec(-2/sqrt(2))").toString(),
            "(3 Pi)/4");
  EXPECT_EQ(Expression("asec(-2)").toString(),
            "(2 Pi)/3");
  EXPECT_EQ(Expression("asec(0)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("asec(2)").toString(),
            "Pi/3");
  EXPECT_EQ(Expression("asec(2/sqrt(2))").toString(),
            "Pi/4");
  EXPECT_EQ(Expression("asec(2/sqrt(3))").toString(),
            "Pi/6");
  EXPECT_EQ(Expression("asec(1)").toString(),
            "0");

  EXPECT_EQ(Expression("acsc(-1)").toString(),
            "-Pi/2");
  EXPECT_EQ(Expression("acsc(-2/sqrt(3))").toString(),
            "-Pi/3");
  EXPECT_EQ(Expression("acsc(-2/sqrt(2))").toString(),
            "-Pi/4");
  EXPECT_EQ(Expression("acsc(-2)").toString(),
            "-Pi/6");
  EXPECT_EQ(Expression("acsc(0)").toString(),
            "ComplexInf");
  EXPECT_EQ(Expression("acsc(2)").toString(),
            "Pi/6");
  EXPECT_EQ(Expression("acsc(2/sqrt(2))").toString(),
            "Pi/4");
  EXPECT_EQ(Expression("acsc(2/sqrt(3))").toString(),
            "Pi/3");
  EXPECT_EQ(Expression("acsc(1)").toString(),
            "Pi/2");

  EXPECT_EQ(Expression("asin(sqrt(5)/10)").toString(),
            "asin(sqrt(5)/10)");
  EXPECT_EQ(Expression("acos(sqrt(5)/10)").toString(),
            "acos(sqrt(5)/10)");
  EXPECT_EQ(Expression("atan(sqrt(5)/10)").toString(),
            "atan(sqrt(5)/10)");
  EXPECT_EQ(Expression("acot(sqrt(5)/10)").toString(),
            "acot(sqrt(5)/10)");
  EXPECT_EQ(Expression("asec(sqrt(5)/10)").toString(),
            "asec(sqrt(5)/10)");
  EXPECT_EQ(Expression("acsc(sqrt(5)/10)").toString(),
            "acsc(sqrt(5)/10)");

  EXPECT_EQ(Expression("asin(x)").toString(),
            "asin(x)");
  EXPECT_EQ(Expression("acos(x)").toString(),
            "acos(x)");
  EXPECT_EQ(Expression("atan(x)").toString(),
            "atan(x)");
  EXPECT_EQ(Expression("acot(x)").toString(),
            "acot(x)");
  EXPECT_EQ(Expression("asec(x)").toString(),
            "asec(x)");
  EXPECT_EQ(Expression("acsc(x)").toString(),
            "acsc(x)");

  EXPECT_EQ(Expression("asin(sqrt(x))").toString(),
            "asin(sqrt(x))");
  EXPECT_EQ(Expression("acos(sqrt(x))").toString(),
            "acos(sqrt(x))");
  EXPECT_EQ(Expression("atan(sqrt(x))").toString(),
            "atan(sqrt(x))");
  EXPECT_EQ(Expression("acot(sqrt(x))").toString(),
            "acot(sqrt(x))");
  EXPECT_EQ(Expression("asec(sqrt(x))").toString(),
            "asec(sqrt(x))");
  EXPECT_EQ(Expression("acsc(sqrt(x))").toString(),
            "acsc(sqrt(x))");

  EXPECT_EQ(Expression("asin(sqrt(x)/2)").toString(),
            "asin(sqrt(x)/2)");
  EXPECT_EQ(Expression("acos(sqrt(x)/2)").toString(),
            "acos(sqrt(x)/2)");
  EXPECT_EQ(Expression("atan(sqrt(x)/2)").toString(),
            "atan(sqrt(x)/2)");
  EXPECT_EQ(Expression("asec(sqrt(x)/2)").toString(),
            "asec(sqrt(x)/2)");
  EXPECT_EQ(Expression("acsc(sqrt(x)/2)").toString(),
            "acsc(sqrt(x)/2)");

  EXPECT_EQ(Expression("asin(-x)").toString(),
            "asin(-x)");
  EXPECT_EQ(Expression("acos(-x)").toString(),
            "acos(-x)");
  EXPECT_EQ(Expression("atan(-x)").toString(),
            "atan(-x)");
  EXPECT_EQ(Expression("acot(-x)").toString(),
            "acot(-x)");
  EXPECT_EQ(Expression("asec(-x)").toString(),
            "asec(-x)");
  EXPECT_EQ(Expression("acsc(-x)").toString(),
            "acsc(-x)");

  EXPECT_EQ(Expression("asin(-sqrt(x))").toString(),
            "asin(-sqrt(x))");
  EXPECT_EQ(Expression("acos(-sqrt(x))").toString(),
            "acos(-sqrt(x))");
  EXPECT_EQ(Expression("atan(-sqrt(x))").toString(),
            "atan(-sqrt(x))");
  EXPECT_EQ(Expression("acot(-sqrt(x))").toString(),
            "acot(-sqrt(x))");
  EXPECT_EQ(Expression("asec(-sqrt(x))").toString(),
            "asec(-sqrt(x))");
  EXPECT_EQ(Expression("acsc(-sqrt(x))").toString(),
            "acsc(-sqrt(x))");

  EXPECT_EQ(Expression("asin(-sqrt(x)/2)").toString(),
            "asin(-sqrt(x)/2)");
  EXPECT_EQ(Expression("acos(-sqrt(x)/2)").toString(),
            "acos(-sqrt(x)/2)");
  EXPECT_EQ(Expression("atan(-sqrt(x)/2)").toString(),
            "atan(-sqrt(x)/2)");
  EXPECT_EQ(Expression("acot(-sqrt(x)/2)").toString(),
            "acot(-sqrt(x)/2)");
  EXPECT_EQ(Expression("asec(-sqrt(x)/2)").toString(),
            "asec(-sqrt(x)/2)");
  EXPECT_EQ(Expression("acsc(-sqrt(x)/2)").toString(),
            "acsc(-sqrt(x)/2)");
}
