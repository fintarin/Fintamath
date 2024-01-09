#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(ExpressionFunctionsTests, addTest) {
  EXPECT_EQ(add(Variable("a"), -1, Expression("b^2")).toString(), "a + b^2 - 1");
  EXPECT_EQ(add(10, Expression("a+2")).toString(), "a + 12");
  EXPECT_EQ(add(Variable("a"), Expression("a+2")).toString(), "2 a + 2");
  EXPECT_EQ(add(Expression("b+2"), Expression("a+2")).toString(), "a + b + 4");
  EXPECT_EQ(add(Expression("10+a^3"), Expression("a^2")).toString(), "a^3 + a^2 + 10");
  EXPECT_EQ(add(Expression("a*b"), Expression("b*a")).toString(), "2 a b");
  EXPECT_EQ(add(Expression("a+b"), Expression("a+b")).toString(), "2 a + 2 b");
}

TEST(ExpressionFunctionsTests, mulTest) {
  EXPECT_EQ(mul(Variable("a"), -1, Expression("a*2")).toString(), "-2 a^2");
  EXPECT_EQ(mul(10, Expression("a+2")).toString(), "10 a + 20");
  EXPECT_EQ(mul(Variable("a"), Expression("a^3+a^2")).toString(), "a^4 + a^3");
  EXPECT_EQ(mul(5, Expression("a+3"), Expression("a+2")).toString(), "5 a^2 + 25 a + 30");
  EXPECT_EQ(mul(Expression("a+b"), Expression("3 b + c")).toString(), "3 a b + a c + 3 b^2 + b c");
}

TEST(ExpressionFunctionsTests, subTest) {
  EXPECT_EQ(sub(Variable("a"), Expression("b^2")).toString(), "a - b^2");
  EXPECT_EQ(sub(10, Expression("a+2")).toString(), "-a + 8");
  EXPECT_EQ(sub(Variable("a"), Expression("a+2")).toString(), "-2");
  EXPECT_EQ(sub(Expression("b+2"), Expression("a+2")).toString(), "-a + b");
  EXPECT_EQ(sub(Expression("10+a^3"), Expression("a^2")).toString(), "a^3 - a^2 + 10");
  EXPECT_EQ(sub(Expression("a*b"), Expression("b*a")).toString(), "0");
  EXPECT_EQ(sub(Expression("a+b"), Expression("a+b")).toString(), "0");
}

TEST(ExpressionFunctionsTests, divTest) {
  EXPECT_EQ(div(Variable("a"), Expression("b^2")).toString(), "a/(b^2)");
  EXPECT_EQ(div(10, Expression("a+2")).toString(), "10/(a + 2)");
  EXPECT_EQ(div(Variable("a"), Expression("a+2")).toString(), "1 - 2/(a + 2)");
  EXPECT_EQ(div(Expression("b+2"), Expression("a+2")).toString(), "(b + 2)/(a + 2)");
  EXPECT_EQ(div(Expression("10+a^3"), Expression("a^2")).toString(), "a + 10/(a^2)");
  EXPECT_EQ(div(Expression("a*b"), Expression("b*a")).toString(), "1");
  EXPECT_EQ(div(Expression("a+b"), Expression("a+b")).toString(), "1");
}

TEST(ExpressionFunctionsTests, negTest) {
  EXPECT_EQ(neg(Expression("a")).toString(), "-a");
  EXPECT_EQ(neg(Expression("a+3")).toString(), "-a - 3");
  EXPECT_EQ(neg(Expression("(a+b)^2")).toString(), "-a^2 - 2 a b - b^2");
}

TEST(ExpressionFunctionsTests, eqvTest) {
  EXPECT_EQ(eqv(Expression("a+3"), Expression("3+a")).toString(), "True");
  EXPECT_EQ(eqv(Expression("a^2"), Expression("a*a+0")).toString(), "True");
  EXPECT_EQ(eqv(Expression("a^2"), Expression("a")).toString(), "a^2 - a = 0");
}

TEST(ExpressionFunctionsTests, neqvTest) {
  EXPECT_EQ(neqv(Expression("a+3"), Expression("3+a")).toString(), "False");
  EXPECT_EQ(neqv(Expression("a^2"), Expression("a*a+0")).toString(), "False");
  EXPECT_EQ(neqv(Expression("a^2"), Expression("a")).toString(), "a^2 - a != 0");
}

TEST(ExpressionFunctionsTests, lessTest) {
  EXPECT_EQ(less(Expression("a+3"), Expression("3+a")).toString(), "False");
  EXPECT_EQ(less(Expression("a^2"), Expression("a*a+0")).toString(), "False");
  EXPECT_EQ(less(Expression("a^2"), Expression("a")).toString(), "a^2 - a < 0");
}

TEST(ExpressionFunctionsTests, moreTest) {
  EXPECT_EQ(more(Expression("a+3"), Expression("3+a")).toString(), "False");
  EXPECT_EQ(more(Expression("a^2"), Expression("a*a+0")).toString(), "False");
  EXPECT_EQ(more(Expression("a^2"), Expression("a")).toString(), "a^2 - a > 0");
}

TEST(ExpressionFunctionsTests, lessEqvTest) {
  EXPECT_EQ(lessEqv(Expression("a+3"), Expression("3+a")).toString(), "True");
  EXPECT_EQ(lessEqv(Expression("a^2"), Expression("a*a+0")).toString(), "True");
  EXPECT_EQ(lessEqv(Expression("a^2"), Expression("a")).toString(), "a^2 - a <= 0");
}

TEST(ExpressionFunctionsTests, moreEqvTest) {
  EXPECT_EQ(moreEqv(Expression("a+3"), Expression("3+a")).toString(), "True");
  EXPECT_EQ(moreEqv(Expression("a^2"), Expression("a*a+0")).toString(), "True");
  EXPECT_EQ(moreEqv(Expression("a^2"), Expression("a")).toString(), "a^2 - a >= 0");
}

TEST(ExpressionFunctionsTests, modTest) {
  EXPECT_EQ(mod(Variable("a"), Expression("b^2")).toString(), "a mod (b^2)");
  EXPECT_EQ(mod(10, Expression("a+2")).toString(), "10 mod (a + 2)");
  EXPECT_EQ(mod(Expression("5/2"), Expression("3")).toString(), "(5/2) mod 3");
  EXPECT_EQ(mod(Expression("5"), Expression("3")).toString(), "2");
}

TEST(ExpressionFunctionsTests, floorTest) {
  EXPECT_EQ(floor(Expression("a+3")).toString(), "floor(a + 3)");
  EXPECT_EQ(floor(Expression("a^4")).toString(), "floor(a^4)");
  EXPECT_EQ(floor(Expression("-333")).toString(), "-333");
  EXPECT_EQ(floor(Expression("2/3")).toString(), "0");
  EXPECT_EQ(floor(Expression("-2/3")).toString(), "-1");
}

TEST(ExpressionFunctionsTests, ceilTest) {
  EXPECT_EQ(ceil(Expression("a+3")).toString(), "ceil(a + 3)");
  EXPECT_EQ(ceil(Expression("a^4")).toString(), "ceil(a^4)");
  EXPECT_EQ(ceil(Expression("-333")).toString(), "-333");
  EXPECT_EQ(ceil(Expression("2/3")).toString(), "1");
  EXPECT_EQ(ceil(Expression("-2/3")).toString(), "0");
}

TEST(ExpressionFunctionsTests, absTest) {
  EXPECT_EQ(abs(Expression("a+3")).toString(), "abs(a + 3)");
  EXPECT_EQ(abs(Expression("a^4")).toString(), "abs(a^4)");
  EXPECT_EQ(abs(Expression("-333")).toString(), "333");
}

TEST(ExpressionFunctionsTests, factorialTest) {
  EXPECT_EQ(factorial(Expression("a+3")).toString(), "(a + 3)!");
  EXPECT_EQ(factorial(Expression("a*3")).toString(), "(3 a)!");
  EXPECT_EQ(factorial(Expression("5")).toString(), "120");
}

TEST(ExpressionFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Expression("4")).toString(), "2");
  EXPECT_EQ(sqrt(Expression("5")).toString(), "sqrt(5)");
  EXPECT_EQ(sqrt(Expression("a^4")).toString(), "sqrt(a^4)");
  EXPECT_EQ(sqrt(Expression("a^2*b*b")).toString(), "sqrt(a^2 b^2)");
  EXPECT_EQ(sqrt(Expression("a^2+b^2+2*a*b")).toString(), "sqrt(a^2 + 2 a b + b^2)");
}

TEST(ExpressionFunctionsTests, powTest) {
  EXPECT_EQ(pow(Expression("a+b"), Expression("0")).toString(), "1");
  EXPECT_EQ(pow(Expression("a^4"), Expression("a")).toString(), "(a^4)^a");
  EXPECT_EQ(pow(Expression("a^4"), Expression("2")).toString(), "a^8");
  EXPECT_EQ(pow(Expression("a*b"), Expression("a+3")).toString(), "(a b)^(a + 3)");
  EXPECT_EQ(pow(Expression("a+2"), Expression("2")).toString(), "a^2 + 4 a + 4");
}

TEST(ExpressionFunctionsTests, expTest) {
  EXPECT_EQ(exp(Expression("a^4")).toString(), "E^(a^4)");
  EXPECT_EQ(exp(Expression("2")).toString(), "E^2");
  EXPECT_EQ(exp(Expression("0")).toString(), "1");
  EXPECT_EQ(exp(Expression("ln(5)")).toString(), "E^ln(5)");
}

TEST(ExpressionFunctionsTests, logTest) {
  EXPECT_EQ(log(Expression("a+b"), Expression("1")).toString(), "0");
  EXPECT_EQ(log(Expression("2*a"), Expression("a+b")).toString(), "log(2 a, a + b)");
  EXPECT_EQ(log(Expression("a"), Expression("a^5")).toString(), "5");
}

TEST(ExpressionFunctionsTests, lnTest) {
  EXPECT_EQ(ln(Expression("E*E")).toString(), "2");
  EXPECT_EQ(ln(Expression("10")).toString(), "ln(10)");
}

TEST(ExpressionFunctionsTests, lbTest) {
  EXPECT_EQ(lb(Expression("1024*a")).toString(), "log(2, 1024 a)");
  EXPECT_EQ(lb(Expression("2+a")).toString(), "log(2, a + 2)");
}

TEST(ExpressionFunctionsTests, lgTest) {
  EXPECT_EQ(lg(Expression("10")).toString(), "1");
  EXPECT_EQ(lg(Expression("E*a")).toString(), "log(10, E a)");
}

TEST(ExpressionFunctionsTests, sinTest) {
  EXPECT_EQ(sin(Expression("5*Pi")).toString(), "0");
  EXPECT_EQ(sin(Expression("Pi/2")).toString(), "1");
  EXPECT_EQ(sin(Expression("a+b")).toString(), "sin(a + b)");
}

TEST(ExpressionFunctionsTests, cosTest) {
  EXPECT_EQ(cos(Expression("5*Pi")).toString(), "-1");
  EXPECT_EQ(cos(Expression("3*Pi/2")).toString(), "0");
  EXPECT_EQ(cos(Expression("8*a")).toString(), "cos(8 a)");
}

TEST(ExpressionFunctionsTests, tanTest) {
  EXPECT_EQ(tan(Expression("0")).toString(), "0");
  EXPECT_EQ(tan(Expression("3*Pi/4")).toString(), "-1");
  EXPECT_EQ(tan(Expression("a^3")).toString(), "tan(a^3)");
}

TEST(ExpressionFunctionsTests, cotTest) {
  EXPECT_EQ(cot(Expression("Pi/4")).toString(), "1");
  EXPECT_EQ(cot(Expression("Pi/2")).toString(), "0");
  EXPECT_EQ(cot(Expression("a/5")).toString(), "cot(a/5)");
}

TEST(ExpressionFunctionsTests, asinTest) {
  EXPECT_EQ(asin(Expression("-1")).toString(), "-Pi/2");
  EXPECT_EQ(asin(Expression("0")).toString(), "0");
  EXPECT_EQ(asin(Expression("1")).toString(), "Pi/2");
  EXPECT_EQ(asin(Expression("a+b")).toString(), "asin(a + b)");
}

TEST(ExpressionFunctionsTests, acosTest) {
  EXPECT_EQ(acos(Expression("-1")).toString(), "Pi");
  EXPECT_EQ(acos(Expression("0")).toString(), "Pi/2");
  EXPECT_EQ(acos(Expression("1")).toString(), "0");
  EXPECT_EQ(acos(Expression("8*a")).toString(), "acos(8 a)");
}

TEST(ExpressionFunctionsTests, atanTest) {
  EXPECT_EQ(atan(Expression("-1")).toString(), "-Pi/4");
  EXPECT_EQ(atan(Expression("0")).toString(), "0");
  EXPECT_EQ(atan(Expression("1")).toString(), "Pi/4");
  EXPECT_EQ(atan(Expression("a^3")).toString(), "atan(a^3)");
}

TEST(ExpressionFunctionsTests, acotTest) {
  EXPECT_EQ(acot(Expression("-1")).toString(), "-Pi/4");
  EXPECT_EQ(acot(Expression("0")).toString(), "Pi/2");
  EXPECT_EQ(acot(Expression("1")).toString(), "Pi/4");
  EXPECT_EQ(acot(Expression("a/5")).toString(), "acot(a/5)");
}

TEST(ExpressionFunctionsTests, sinhTest) {
  EXPECT_EQ(sinh(Expression("-0.5")).toString(), "-sinh(1/2)");
  EXPECT_EQ(sinh(Expression("0")).toString(), "0");
  EXPECT_EQ(sinh(Expression("0.5")).toString(), "sinh(1/2)");
}

TEST(ExpressionFunctionsTests, coshTest) {
  EXPECT_EQ(cosh(Expression("-0.5")).toString(), "cosh(1/2)");
  EXPECT_EQ(cosh(Expression("0")).toString(), "1");
  EXPECT_EQ(cosh(Expression("0.5")).toString(), "cosh(1/2)");
}

TEST(ExpressionFunctionsTests, tanhTest) {
  EXPECT_EQ(tanh(Expression("-0.5")).toString(), "-tanh(1/2)");
  EXPECT_EQ(tanh(Expression("0")).toString(), "0");
  EXPECT_EQ(tanh(Expression("0.5")).toString(), "tanh(1/2)");
}

TEST(ExpressionFunctionsTests, cothTest) {
  EXPECT_EQ(coth(Expression("-0.5")).toString(), "-coth(1/2)");
  EXPECT_EQ(coth(Expression("0")).toString(), "ComplexInf");
  EXPECT_EQ(coth(Expression("0.5")).toString(), "coth(1/2)");
}

TEST(ExpressionFunctionsTests, asinhTest) {
  EXPECT_EQ(asinh(Expression("-0.5")).toString(), "asinh(-1/2)");
  EXPECT_EQ(asinh(Expression("0")).toString(), "0");
  EXPECT_EQ(asinh(Expression("0.5")).toString(), "asinh(1/2)");
}

TEST(ExpressionFunctionsTests, acoshTest) {
  EXPECT_EQ(acosh(Expression("-0.5")).toString(), "acosh(-1/2)");
  EXPECT_EQ(acosh(Expression("0")).toString(), "(I Pi)/2");
  EXPECT_EQ(acosh(Expression("0.5")).toString(), "acosh(1/2)");
}

TEST(ExpressionFunctionsTests, atanhTest) {
  EXPECT_EQ(atanh(Expression("-0.5")).toString(), "atanh(-1/2)");
  EXPECT_EQ(atanh(Expression("0")).toString(), "0");
  EXPECT_EQ(atanh(Expression("0.5")).toString(), "atanh(1/2)");
}

TEST(ExpressionFunctionsTests, acothTest) {
  EXPECT_EQ(acoth(Expression("-0.5")).toString(), "acoth(-1/2)");
  EXPECT_EQ(acoth(Expression("0")).toString(), "(I Pi)/2");
  EXPECT_EQ(acoth(Expression("0.5")).toString(), "acoth(1/2)");
}

TEST(ExpressionFunctionsTests, derivativeTest) {
  EXPECT_EQ(derivative(Expression("1"), Expression("a")).toString(), "0");
  EXPECT_EQ(derivative(Expression("a"), Expression("a")).toString(), "1");
  EXPECT_EQ(derivative(Expression("(a+5)"), Expression("a")).toString(), "1");
  EXPECT_EQ(derivative(Expression("sin(a^2)"), Expression("a")).toString(), "2 a cos(a^2)");
  EXPECT_EQ(derivative(Expression("(ln(a)/tan(a))^(1/2)"), Expression("a")).toString(), "-(sqrt(cot(a) ln(a)) csc(a)^2 tan(a))/2 + sqrt(cot(a) ln(a))/(2 a ln(a))");
}

TEST(ExpressionFunctionsTests, notTest) {
  EXPECT_EQ(notL(Expression("True")).toString(), "False");
  EXPECT_EQ(notL(Expression("False")).toString(), "True");
  EXPECT_EQ(notL(Expression("a")).toString(), "~a");
  EXPECT_EQ(notL(Expression("1=1")).toString(), "False");
}

TEST(ExpressionFunctionsTests, andTest) {
  EXPECT_EQ(andL(Expression("True"), Expression("True")).toString(), "True");
  EXPECT_EQ(andL(Expression("False"), Expression("True")).toString(), "False");
  EXPECT_EQ(andL(Expression("a"), Expression("b")).toString(), "a & b");
  EXPECT_EQ(andL(Expression("a=a"), Expression("b=b")).toString(), "True");
}

TEST(ExpressionFunctionsTests, orTest) {
  EXPECT_EQ(orL(Expression("True"), Expression("True")).toString(), "True");
  EXPECT_EQ(orL(Expression("False"), Expression("True")).toString(), "True");
  EXPECT_EQ(orL(Expression("a"), Expression("b")).toString(), "a | b");
  EXPECT_EQ(orL(Expression("a!=a"), Expression("b!=b")).toString(), "False");
}

TEST(ExpressionFunctionsTests, eTest) {
  EXPECT_EQ(e().toString(), "E");
}

TEST(ExpressionFunctionsTests, piTest) {
  EXPECT_EQ(pi().toString(), "Pi");
}

TEST(ExpressionFunctionsTests, infTest) {
  EXPECT_EQ(inf().toString(), "Inf");
}

TEST(ExpressionFunctionsTests, negInfTest) {
  EXPECT_EQ(negInf().toString(), "-Inf");
}

TEST(ExpressionFunctionsTests, complexInfTest) {
  EXPECT_EQ(complexInf().toString(), "ComplexInf");
}

TEST(ExpressionFunctionsTests, solveTest) {
  EXPECT_EQ(solve(Expression("x - 10 = 0")).toString(), "x = 10");
  EXPECT_EQ(solve(Expression("-10 - x = 0")).toString(), "x = -10");

  EXPECT_EQ(solve(Expression("z - 10 - I = 0")).toString(), "z = 10 + I");
  EXPECT_EQ(solve(Expression("(6 + 3I)^2 = 4I - 30z")).toString(), "z = -9/10 - 16/15 I");

  EXPECT_EQ(solve(Expression("x^2 - 10 = 39")).toString(), "x = -7 | x = 7");
  EXPECT_EQ(solve(Expression("x^2 = 0")).toString(), "x = 0");
  EXPECT_EQ(solve(Expression("x^2 = 1")).toString(), "x = -1 | x = 1");
  EXPECT_EQ(solve(Expression("x^2 - 2x - 3 = 0")).toString(), "x = -1 | x = 3");
  EXPECT_EQ(solve(Expression("15 - 2x - x^2 = 0")).toString(), "x = -5 | x = 3");
  EXPECT_EQ(solve(Expression("x^2 + 12x + 36 = 0")).toString(), "x = -6");
  EXPECT_EQ(solve(Expression("x^2 + 12x = 0")).toString(), "x = -12 | x = 0");
  EXPECT_EQ(solve(Expression("x^2 - 23x - 3 = 0")).toString(), "x = -sqrt(541)/2 + 23/2 | x = sqrt(541)/2 + 23/2");
  EXPECT_EQ(solve(Expression("-12x^2 - 23x + 30 = 0")).toString(), "x = -sqrt(1969)/24 - 23/24 | x = sqrt(1969)/24 - 23/24");
  EXPECT_EQ(solve(Expression("-33x^2 - x + 34 = 0")).toString(), "x = -34/33 | x = 1");
  EXPECT_EQ(solve(Expression("2x^2 + 2sqrt(2)x + 1 = 0")).toString(), "x = -sqrt(2)/2");

  EXPECT_EQ(solve(Expression("x^2 = -1")).toString(), "x = -I | x = I");
  EXPECT_EQ(solve(Expression("x^2 + 4x + 5 = 0")).toString(), "x = -2 - I | x = -2 + I");
  EXPECT_EQ(solve(Expression("2x^2 + x + 1 = 0")).toString(), "x = -(I sqrt(7))/4 - 1/4 | x = (I sqrt(7))/4 - 1/4");
  EXPECT_EQ(solve(Expression("x^2 + 3x + 5 = 0")).toString(), "x = -(I sqrt(11))/2 - 3/2 | x = (I sqrt(11))/2 - 3/2");

  // TODO: implement cubic equations
  EXPECT_EQ(solve(Expression("x^3 - 3x^2 + 3x - 1 = 0")).toString(), "x^3 - 3 x^2 + 3 x - 1 = 0"); // TODO: x = 1
  // EXPECT_EQ(solve(Expression("x^3 - 6x^2 + 11x - 6 = 0")).toString(), "x = 1 | x = 2 | x = 3");
  // EXPECT_EQ(solve(Expression("x^3 + 2x^2 - 5x - 6 = 0")).toString(), "x = -3 | x = -1 | x = 2");
  // EXPECT_EQ(solve(Expression("x^3 = 0")).toString(), "x = 0");
  // EXPECT_EQ(solve(Expression("x^3 + 1 = 0")).toString(), "x = -1");
  // EXPECT_EQ(solve(Expression("x^3 - 1 = 0")).toString(), "x = 1");
  // EXPECT_EQ(solve(Expression("x^3 + 2x^2 + x = 0")).toString(), "x = -1 | x = 0");
  // EXPECT_EQ(solve(Expression("-x^3 + 5x^2 - 8x + 4 = 0")).toString(), "x = 1 | x = 2");
  // EXPECT_EQ(solve(Expression("-2x^3 + 4x^2 + 4x - 8 = 0")).toString(), "x = -1 | x = 1 | x = 2");
  // EXPECT_EQ(solve(Expression("2x^3 - 3x^2 - 11x + 6 = 0")).toString(), "x = -2 | x = 1/2 | x = 3");
  // EXPECT_EQ(solve(Expression("3x^3 - 3x^2 - 12x - 8 = 0")).toString(),
  //           "1/9 (3 + (1485 - 162 sqrt(23))^(1/3) + 3 (55 + 6 sqrt(23))^(1/3))");

  EXPECT_EQ(solve(Expression("x < 1")).toString(), "x < 1");
  EXPECT_EQ(solve(Expression("x < -10")).toString(), "x < -10");
  EXPECT_EQ(solve(Expression("x! = 0")).toString(), "x! = 0");

  // TODO: implement quadric inequalities
  EXPECT_EQ(solve(Expression("x^2 + 2 x - 1 < 0")).toString(), "x^2 + 2 x - 1 < 0");

  EXPECT_EQ(solve(Expression("15x^2 + sin(25)x - 10% = Ey")).toString(), "x^2 + (sin(25) x)/15 - (E y)/15 - 1/150 = 0");
  EXPECT_EQ(solve(Expression("x + x_1 + x_2 + y + y_1 = 0")).toString(), "x + x_1 + x_2 + y + y_1 = 0");
  EXPECT_EQ(solve(Expression("-x^a = 0")).toString(), "x^a = 0");
  EXPECT_EQ(solve(Expression("sin(x) = 0")).toString(), "sin(x) = 0");
  EXPECT_EQ(solve(Expression("x^2 + y = 0")).toString(), "x^2 + y = 0");
  EXPECT_EQ(solve(Expression("x y = 0")).toString(), "x y = 0");
  EXPECT_EQ(solve(Expression("2 x^a = 0")).toString(), "x^a = 0");
  EXPECT_EQ(solve(Expression("x^b a = 0")).toString(), "a x^b = 0");
  EXPECT_EQ(solve(Expression("x/y = 0")).toString(), "x = 0");
  EXPECT_EQ(solve(Expression("x^2 - 2*sin(2) = 0")).toString(), "x = -sqrt(8 sin(2))/2 | x = sqrt(8 sin(2))/2");
  EXPECT_EQ(solve(Expression("x = x sqrt(x)")).toString(), "x^(3/2) - x = 0");
  EXPECT_EQ(solve(Expression("x = 3^x")).toString(), "x - 3^x = 0");

  EXPECT_EQ(solve(Expression("E = Ey")).toString(), "y = 1");
  EXPECT_EQ(solve(Expression("sin(4) = sin(4) y")).toString(), "y = 1");
  EXPECT_EQ(solve(Expression("E >= Ey")).toString(), "y <= 1");
  EXPECT_EQ(solve(Expression("sin(4) >= sin(4) y")).toString(), "y >= 1");
  EXPECT_EQ(solve(Expression("x >= x sqrt(x)")).toString(), "x^(3/2) - x <= 0");
  EXPECT_EQ(solve(Expression("x >= x^(1/100)")).toString(), "x - root(x, 100) >= 0");
}

TEST(ExpressionFunctionsTests, solveApproximateTest) {
  Expression expr;
  Variable x("x");

  expr = pow(x + 1, 6);
  EXPECT_EQ(expr.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");

  expr = solve(expr);
  EXPECT_EQ(expr.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");

  expr = expr.approximate(2);
  EXPECT_EQ(expr.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");

  expr = pow(x + 1, 7);
  EXPECT_EQ(expr.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");

  expr = solve(expr);
  EXPECT_EQ(expr.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");

  expr = expr.approximate(2);
  EXPECT_EQ(expr.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");
}
