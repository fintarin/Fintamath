#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyDerivativeTests, simplifyTest) {
  EXPECT_EQ(Expression("derivative(2, x)").toString(),
            "0");
  EXPECT_EQ(Expression("derivative(2 + I, x)").toString(),
            "0");
  EXPECT_EQ(Expression("derivative(E, x)").toString(),
            "0");
  EXPECT_EQ(Expression("derivative(x, x)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x, y)").toString(),
            "0");
  EXPECT_EQ(Expression("derivative(x_1, x_1)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x_1, x_2)").toString(),
            "0");
  EXPECT_EQ(Expression("derivative(-x, x)").toString(),
            "-1");
  EXPECT_EQ(Expression("derivative(x + y, x)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x + 2, x)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x + (2+I), x)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x - y, x)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x - 2, x)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x - (2+I), x)").toString(),
            "1");
  EXPECT_EQ(Expression("derivative(x * y, x)").toString(),
            "y");
  EXPECT_EQ(Expression("derivative(x * 2, x)").toString(),
            "2");
  EXPECT_EQ(Expression("derivative(x * (2+I), x)").toString(),
            "2 + I");
  EXPECT_EQ(Expression("derivative(x / y, x)").toString(),
            "1/y");
  EXPECT_EQ(Expression("derivative(y / x, x)").toString(),
            "-y/(x^2)");
  EXPECT_EQ(Expression("derivative(x / 2, x)").toString(),
            "1/2");
  EXPECT_EQ(Expression("derivative(2 / x, x)").toString(),
            "-2/(x^2)");
  EXPECT_EQ(Expression("derivative(x / (2+I), x)").toString(),
            "2/5 - 1/5 I");
  EXPECT_EQ(Expression("derivative((2+I) / x, x)").toString(),
            "-(2 + I)/(x^2)");
  EXPECT_EQ(Expression("derivative(x mod y, x)").toString(),
            "derivative(x mod y, x)");
  EXPECT_EQ(Expression("derivative(y mod x, x)").toString(),
            "derivative(y mod x, x)");
  EXPECT_EQ(Expression("derivative(x mod 2, x)").toString(),
            "derivative(x mod 2, x)");
  EXPECT_EQ(Expression("derivative(2 mod x, x)").toString(),
            "derivative(2 mod x, x)");
  EXPECT_EQ(Expression("derivative(x ^ x, x)").toString(),
            "x^x ln(x) + x^x");
  EXPECT_EQ(Expression("derivative(x ^ y, x)").toString(),
            "x^(y - 1) y");
  EXPECT_EQ(Expression("derivative(y ^ x, x)").toString(),
            "y^x ln(y)");
  EXPECT_EQ(Expression("derivative(x ^ 2, x)").toString(),
            "2 x");
  EXPECT_EQ(Expression("derivative(2 ^ x, x)").toString(),
            "2^x ln(2)");
  EXPECT_EQ(Expression("derivative(x ^ (3/5), x)").toString(),
            "3/(5 x^(2/5))");
  EXPECT_EQ(Expression("derivative((3/5) ^ x, x)").toString(),
            "(3/5)^x ln(3/5)");
  EXPECT_EQ(Expression("derivative(x ^ (-3/5), x)").toString(),
            "-3/(5 x^(8/5))");
  EXPECT_EQ(Expression("derivative((-3/5) ^ x, x)").toString(),
            "(-3/5)^x ln(-3/5)");
  EXPECT_EQ(Expression("derivative(x ^ (2+I), x)").toString(),
            "(2 + I) x^(1 + I)");
  EXPECT_EQ(Expression("derivative((2+I) ^ x, x)").toString(),
            "(2 + I)^x ln(2 + I)");
  EXPECT_EQ(Expression("derivative(x deg, x)").toString(),
            "Pi/180");
  EXPECT_EQ(Expression("derivative(x%, x)").toString(),
            "1/100");
  EXPECT_EQ(Expression("derivative(x!, x)").toString(),
            "derivative(x!, x)");
  EXPECT_EQ(Expression("derivative(sqrt(x), x)").toString(),
            "1/(2 sqrt(x))");
  EXPECT_EQ(Expression("derivative(root(x, 3), x)").toString(),
            "1/(3 x^(2/3))");
  EXPECT_EQ(Expression("derivative(root(x, 10), x)").toString(),
            "1/(10 x^(9/10))");
  EXPECT_EQ(Expression("derivative(exp(x), x)").toString(),
            "E^x");
  EXPECT_EQ(Expression("derivative(ln(x), x)").toString(),
            "1/x");
  EXPECT_EQ(Expression("derivative(lb(x), x)").toString(),
            "1/(ln(2) x)");
  EXPECT_EQ(Expression("derivative(lg(x), x)").toString(),
            "1/(ln(10) x)");
  EXPECT_EQ(Expression("derivative(log(x, y), x)").toString(),
            "-ln(y)/(x ln(x)^2)");
  EXPECT_EQ(Expression("derivative(log(y, x), x)").toString(),
            "1/(x ln(y))");
  EXPECT_EQ(Expression("derivative(log(x, 2), x)").toString(),
            "-ln(2)/(x ln(x)^2)");
  EXPECT_EQ(Expression("derivative(log(2, x), x)").toString(),
            "1/(ln(2) x)");
  EXPECT_EQ(Expression("derivative(log(x, (3/5)), x)").toString(),
            "-ln(3/5)/(x ln(x)^2)");
  EXPECT_EQ(Expression("derivative(log((3/5), x), x)").toString(),
            "1/(ln(3/5) x)");
  EXPECT_EQ(Expression("derivative(log(x, (-3/5)), x)").toString(),
            "-ln(-3/5)/(x ln(x)^2)");
  EXPECT_EQ(Expression("derivative(log((-3/5), x), x)").toString(),
            "1/(ln(-3/5) x)");
  EXPECT_EQ(Expression("derivative(log(x, (2+I)), x)").toString(),
            "-ln(2 + I)/(x ln(x)^2)");
  EXPECT_EQ(Expression("derivative(log((2+I), x), x)").toString(),
            "1/(ln(2 + I) x)");
  EXPECT_EQ(Expression("derivative(sin(x), x)").toString(),
            "cos(x)");
  EXPECT_EQ(Expression("derivative(sin(x^2), x)").toString(),
            "2 x cos(x^2)");
  EXPECT_EQ(Expression("derivative(cos(x), x)").toString(),
            "-sin(x)");
  EXPECT_EQ(Expression("derivative(cos(x^2), x)").toString(),
            "-2 x sin(x^2)");
  EXPECT_EQ(Expression("derivative(tan(x), x)").toString(),
            "sec(x)^2");
  EXPECT_EQ(Expression("derivative(tan(x^2), x)").toString(),
            "2 x sec(x^2)^2");
  EXPECT_EQ(Expression("derivative(cot(x), x)").toString(),
            "-csc(x)^2");
  EXPECT_EQ(Expression("derivative(cot(x^2), x)").toString(),
            "-2 x csc(x^2)^2");
  EXPECT_EQ(Expression("derivative(sec(x), x)").toString(),
            "sec(x)^2 sin(x)");
  EXPECT_EQ(Expression("derivative(sec(x^2), x)").toString(),
            "2 x sec(x^2)^2 sin(x^2)");
  EXPECT_EQ(Expression("derivative(csc(x), x)").toString(),
            "-csc(x)^2 cos(x)");
  EXPECT_EQ(Expression("derivative(csc(x^2), x)").toString(),
            "-2 x csc(x^2)^2 cos(x^2)");
  EXPECT_EQ(Expression("derivative(asin(x), x)").toString(),
            "1/sqrt(-x^2 + 1)");
  EXPECT_EQ(Expression("derivative(asin(x^2), x)").toString(),
            "(2 x)/sqrt(-x^4 + 1)");
  EXPECT_EQ(Expression("derivative(acos(x), x)").toString(),
            "-1/sqrt(-x^2 + 1)");
  EXPECT_EQ(Expression("derivative(acos(x^2), x)").toString(),
            "-(2 x)/sqrt(-x^4 + 1)");
  EXPECT_EQ(Expression("derivative(atan(x), x)").toString(),
            "1/(x^2 + 1)");
  EXPECT_EQ(Expression("derivative(atan(x^2), x)").toString(),
            "(2 x)/(x^4 + 1)");
  EXPECT_EQ(Expression("derivative(acot(x), x)").toString(),
            "-1/(x^2 + 1)");
  EXPECT_EQ(Expression("derivative(acot(x^2), x)").toString(),
            "-(2 x)/(x^4 + 1)");
  EXPECT_EQ(Expression("derivative(asec(x), x)").toString(),
            "1/(sqrt(1 - 1/(x^2)) x^2)");
  EXPECT_EQ(Expression("derivative(asec(x^2), x)").toString(),
            "2/(sqrt(1 - 1/(x^4)) x^3)");
  EXPECT_EQ(Expression("derivative(acsc(x), x)").toString(),
            "-1/(sqrt(1 - 1/(x^2)) x^2)");
  EXPECT_EQ(Expression("derivative(acsc(x^2), x)").toString(),
            "-2/(sqrt(1 - 1/(x^4)) x^3)");
  EXPECT_EQ(Expression("derivative(sinh(x), x)").toString(),
            "cosh(x)");
  EXPECT_EQ(Expression("derivative(sinh(x^2), x)").toString(),
            "2 x cosh(x^2)");
  EXPECT_EQ(Expression("derivative(cosh(x), x)").toString(),
            "sinh(x)");
  EXPECT_EQ(Expression("derivative(cosh(x^2), x)").toString(),
            "2 x sinh(x^2)");
  EXPECT_EQ(Expression("derivative(tanh(x), x)").toString(),
            "sech(x)^2");
  EXPECT_EQ(Expression("derivative(tanh(x^2), x)").toString(),
            "2 x sech(x^2)^2");
  EXPECT_EQ(Expression("derivative(coth(x), x)").toString(),
            "-csch(x)^2");
  EXPECT_EQ(Expression("derivative(coth(x^2), x)").toString(),
            "-2 x csch(x^2)^2");
  EXPECT_EQ(Expression("derivative(sech(x), x)").toString(),
            "-sech(x)^2 sinh(x)");
  EXPECT_EQ(Expression("derivative(sech(x^2), x)").toString(),
            "-2 x sech(x^2)^2 sinh(x^2)");
  EXPECT_EQ(Expression("derivative(csch(x), x)").toString(),
            "-csch(x)^2 cosh(x)");
  EXPECT_EQ(Expression("derivative(csch(x^2), x)").toString(),
            "-2 x csch(x^2)^2 cosh(x^2)");
  EXPECT_EQ(Expression("derivative(asinh(x), x)").toString(),
            "1/sqrt(x^2 + 1)");
  EXPECT_EQ(Expression("derivative(asinh(x^2), x)").toString(),
            "(2 x)/sqrt(x^4 + 1)");
  EXPECT_EQ(Expression("derivative(acosh(x), x)").toString(),
            "1/(sqrt(x + 1) sqrt(x - 1))");
  EXPECT_EQ(Expression("derivative(acosh(x^2), x)").toString(),
            "(2 x)/(sqrt(x^2 + 1) sqrt(x^2 - 1))");
  EXPECT_EQ(Expression("derivative(atanh(x), x)").toString(),
            "-1/(x^2 - 1)");
  EXPECT_EQ(Expression("derivative(atanh(x^2), x)").toString(),
            "-(2 x)/(x^4 - 1)");
  EXPECT_EQ(Expression("derivative(acoth(x), x)").toString(),
            "-1/(x^2 - 1)");
  EXPECT_EQ(Expression("derivative(acoth(x^2), x)").toString(),
            "-(2 x)/(x^4 - 1)");
  EXPECT_EQ(Expression("derivative(asech(x), x)").toString(),
            "-1/(sqrt(1 + 1/x) sqrt(-1 + 1/x) x^2)");
  EXPECT_EQ(Expression("derivative(asech(x^2), x)").toString(),
            "-2/(sqrt(1 + 1/(x^2)) sqrt(-1 + 1/(x^2)) x^3)");
  EXPECT_EQ(Expression("derivative(acsch(x), x)").toString(),
            "-1/(sqrt(1 + 1/(x^2)) x^2)");
  EXPECT_EQ(Expression("derivative(acsch(x^2), x)").toString(),
            "-2/(sqrt(1 + 1/(x^4)) x^3)");
  EXPECT_EQ(Expression("derivative(abs(x), x)").toString(),
            "derivative(abs(x), x)");
  EXPECT_EQ(Expression("derivative(sign(x), x)").toString(),
            "derivative(sign(x), x)");
  EXPECT_EQ(Expression("derivative(floor(x), x)").toString(),
            "derivative(floor(x), x)");
  EXPECT_EQ(Expression("derivative(ceil(x), x)").toString(),
            "derivative(ceil(x), x)");
  EXPECT_EQ(Expression("derivative(min(x, y), x)").toString(),
            "derivative(min(x, y), x)");
  EXPECT_EQ(Expression("derivative(max(x, y), x)").toString(),
            "derivative(max(x, y), x)");
  EXPECT_EQ(Expression("derivative(integral(x!, x), x)").toString(),
            "derivative(integral(x!, x), x)");
  EXPECT_EQ(Expression("derivative(a b x, x)").toString(),
            "a b");
  EXPECT_EQ(Expression("derivative(a b c x, x)").toString(),
            "a b c");
  EXPECT_EQ(Expression("derivative(a x y, x)").toString(),
            "a y");
  EXPECT_EQ(Expression("derivative(x y z, x)").toString(),
            "y z");
  EXPECT_EQ(Expression("derivative(x y z z_1, x)").toString(),
            "y z z_1");
  EXPECT_EQ(Expression("derivative(3x^2 - 2x, x)").toString(),
            "6 x - 2");
  EXPECT_EQ(Expression("derivative(x^4 - 3x^3 + 2x - 1, x)").toString(),
            "4 x^3 - 9 x^2 + 2");
  EXPECT_EQ(Expression("derivative(x^2 cos(x), x)").toString(),
            "-x^2 sin(x) + 2 x cos(x)");
  EXPECT_EQ(Expression("derivative(E^(x^2 + 2x), x)").toString(),
            "2 E^(x^2 + 2 x) x + 2 E^(x^2 + 2 x)"); // TODO: 2 E^(x^2 + 2 x) (x + 1)
  EXPECT_EQ(Expression("derivative(E^sin(x), x)").toString(),
            "E^sin(x) cos(x)");
  EXPECT_EQ(Expression("derivative(5E^(-x^3), x)").toString(),
            "-15 E^(-x^3) x^2");
  EXPECT_EQ(Expression("derivative(8^(x^2 - 5x), x)").toString(),
            "(16*8^(x^2 - 5 x - 1) x - 40*8^(x^2 - 5 x - 1)) ln(8)"); // TODO: simplify this
  EXPECT_EQ(Expression("derivative((1 + 5x)^3, x)").toString(),
            "375 x^2 + 150 x + 15");
  EXPECT_EQ(Expression("derivative(x^5 (2 - x/3 + 3x^2), x)").toString(),
            "21 x^6 - 2 x^5 + 10 x^4");
  EXPECT_EQ(Expression("derivative(x^3 3^x, x)").toString(),
            "3^(x + 1) x^2 + 3^x x^3 ln(3)");
  EXPECT_EQ(Expression("derivative(ln(3x + 5), x)").toString(),
            "3/(3 x + 5)");
  EXPECT_EQ(Expression("derivative(ln(x^5 - 2x^2 + 5), x)").toString(),
            "(5 x^4 - 4 x)/(x^5 - 2 x^2 + 5)");
  EXPECT_EQ(Expression("derivative(lb(sin(x)^2), x)").toString(),
            "(2 cot(x))/ln(2)");
  EXPECT_EQ(Expression("derivative(root(2 + x^4, 3), x)").toString(),
            "(4 x^3)/(3 (x^4 + 2)^(2/3))");
  EXPECT_EQ(Expression("derivative(sqrt(x) + 5/root(x, 5) - 1/x^9 + 7/(9x^5), x)").toString(),
            "9/(x^10) - 35/(9 x^6) - 1/(x^(6/5)) + 1/(2 sqrt(x))");
  EXPECT_EQ(Expression("derivative(cos(5x), x)").toString(),
            "-5 sin(5 x)");
  EXPECT_EQ(Expression("derivative(asin(5x), x)").toString(),
            "5/sqrt(-25 x^2 + 1)");
  EXPECT_EQ(Expression("derivative(sin(x)^2, x)").toString(),
            "sin(2 x)");
  EXPECT_EQ(Expression("derivative(cos(x)^2, x)").toString(),
            "-sin(2 x)");
  EXPECT_EQ(Expression("derivative(ln(cos(3x)), x)").toString(),
            "-3 tan(3 x)");
  EXPECT_EQ(Expression("derivative(log(sin(x^5), tan(x^3)), x)").toString(),
            "(3 sec(x^3)^2 x^2 cos(x^3) csc(x^3))/ln(sin(x^5)) - (5 x^4 ln(tan(x^3)) cos(x^5) csc(x^5))/(ln(sin(x^5))^2)");
  EXPECT_EQ(Expression("derivative(acos(4x + 5)^5, x)").toString(),
            "-(20 acos(4 x + 5)^4)/sqrt(-16 x^2 - 40 x - 24)");
  EXPECT_EQ(Expression("derivative(sin(sin(sin(x))), x)").toString(),
            "cos(sin(sin(x))) cos(sin(x)) cos(x)");
  EXPECT_EQ(Expression("derivative(cos(tan(cot(x))), x)").toString(),
            "sec(cot(x))^2 csc(x)^2 sin(tan(cot(x)))");
  EXPECT_EQ(Expression("derivative(a b cos(x), x)").toString(),
            "-a b sin(x)");
  EXPECT_EQ(Expression("derivative(a x cos(x) ln(x) sign(x), x)").toString(),
            "a ln(x) cos(x) sign(x) + a cos(x) sign(x) + a x ln(x) (-sin(x) sign(x) + cos(x) derivative(sign(x), x))");
  EXPECT_EQ(Expression("derivative(a * c * cos(x)/(x^2 + 1), x)").toString(),
            "-(a c x^2 sin(x) + a c sin(x) + 2 a c x cos(x))/(x^4 + 2 x^2 + 1)");
  EXPECT_EQ(Expression("derivative((2x^3)/tan(x), x)").toString(),
            "-2 csc(x)^2 x^3 + 6 x^2 cot(x)"); // TODO: -2 x^3 csc(x)^2 + 6 x^2 cot(x)
  EXPECT_EQ(Expression("derivative(acos(x)/(x^2 + 1), x)").toString(),
            "-(x^2 + 2 x sqrt(-x^2 + 1) acos(x) + 1)/(sqrt(-x^2 + 1) x^4 + 2 sqrt(-x^2 + 1) x^2 + sqrt(-x^2 + 1))");
  EXPECT_EQ(Expression("derivative(sin(x)/sinh(x), x)").toString(),
            "-csch(x)^2 sin(x) cosh(x) + cos(x) csch(x)");
  EXPECT_EQ(Expression("derivative(tan(x)/tanh(x), x)").toString(),
            "sec(x)^2 coth(x) - csch(x)^2 tan(x)");
  EXPECT_EQ(Expression("derivative(derivative(derivative(sin(x^3), x), x), x)").toString(),
            "-27 x^6 cos(x^3) - 54 x^3 sin(x^3) + 6 cos(x^3)");
  EXPECT_EQ(Expression("derivative(x^2, x) + derivative(y^2, y)").toString(),
            "2 x + 2 y");
  EXPECT_EQ(Expression("derivative(sin(x^3), x) + derivative(cos(y^3), y) / derivative(tan(ln(y)), y)").toString(),
            "3 x^2 cos(x^3) - (3 y^3 sin(y^3))/(sec(ln(y))^2)");
}
