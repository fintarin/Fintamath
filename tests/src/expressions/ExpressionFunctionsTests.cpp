#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(ExpressionFunctionsTests, sumTest) {
  EXPECT_EQ(sum(Variable("a"), -1, Expression("b^2")).toString(), "a + b^2 - 1");
  EXPECT_EQ(sum(10, Expression("a+2")).toString(), "a + 12");
  EXPECT_EQ(sum(Variable("a"), Expression("a+2")).toString(), "2 a + 2");
  EXPECT_EQ(sum(Expression("b+2"), Expression("a+2")).toString(), "a + b + 4");
  EXPECT_EQ(sum(Expression("10+a^3"), Expression("a^2")).toString(), "a^3 + a^2 + 10");
  EXPECT_EQ(sum(Expression("a*b"), Expression("b*a")).toString(), "2 a b");
  EXPECT_EQ(sum(Expression("a+b"), Expression("a+b")).toString(), "2 a + 2 b");
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
  EXPECT_EQ(div(Variable("a"), Expression("b^2")).toString(), "a/b^2");
  EXPECT_EQ(div(10, Expression("a+2")).toString(), "10/(a + 2)");
  EXPECT_EQ(div(Variable("a"), Expression("a+2")).toString(), "a/(a + 2)");
  EXPECT_EQ(div(Expression("b+2"), Expression("a+2")).toString(), "(b + 2)/(a + 2)");
  EXPECT_EQ(div(Expression("10+a^3"), Expression("a^2")).toString(), "(a^3 + 10)/a^2"); // TODO: polymom division
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
  EXPECT_EQ(moveEqv(Expression("a+3"), Expression("3+a")).toString(), "True");
  EXPECT_EQ(moveEqv(Expression("a^2"), Expression("a*a+0")).toString(), "True");
  EXPECT_EQ(moveEqv(Expression("a^2"), Expression("a")).toString(), "a^2 - a >= 0");
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
  // TODO: sqrt
  EXPECT_EQ(sqrt(Expression("a^4")).toString(), "sqrt(a^4)");
  EXPECT_EQ(sqrt(Expression("a^2*b*b")).toString(), "sqrt(a^2 b^2)");
  EXPECT_EQ(sqrt(Expression("a^2+b^2+2*a*b")).toString(), "sqrt(a^2 + 2 a b + b^2)");
}

TEST(ExpressionFunctionsTests, powTest) {
  EXPECT_EQ(pow(Expression("a+b"), Expression("0")).toString(), "1");
  EXPECT_EQ(pow(Expression("a^4"), Expression("a")).toString(), "a^(4 a)");
  EXPECT_EQ(pow(Expression("a^4"), Expression("2")).toString(), "a^8");
  EXPECT_EQ(pow(Expression("a*b"), Expression("a+3")).toString(), "a^(a + 3) b^(a + 3)");
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
  EXPECT_EQ(log(Expression("2*a"), Expression("a+b")).toString(), "ln(a + b)/ln(2 a)");
  EXPECT_EQ(log(Expression("a"), Expression("a^5")).toString(), "ln(a^5)/ln(a)"); // TODO logarithms
}

TEST(ExpressionFunctionsTests, lnTest) {
  EXPECT_EQ(ln(Expression("E*E")).toString(), "ln(E^2)"); // TODO logarithms
  EXPECT_EQ(ln(Expression("10")).toString(), "ln(10)");
}

TEST(ExpressionFunctionsTests, lbTest) {
  EXPECT_EQ(lb(Expression("1024*a")).toString(), "ln(1024 a)/ln(2)"); // TODO logarithms
  EXPECT_EQ(lb(Expression("2+a")).toString(), "ln(a + 2)/ln(2)");     // TODO logarithms
}

TEST(ExpressionFunctionsTests, lgTest) {
  EXPECT_EQ(lg(Expression("10")).toString(), "1");
  EXPECT_EQ(lg(Expression("E*a")).toString(), "ln(E a)/ln(10)");
}

TEST(ExpressionFunctionsTests, sinTest) {
  EXPECT_EQ(sin(Expression("5*Pi")).toString(), "sin(5 Pi)"); // TODO trigonometry
  EXPECT_EQ(sin(Expression("Pi/2")).toString(), "sin(1/2 Pi)"); // TODO trigonometry
  EXPECT_EQ(sin(Expression("a+b")).toString(), "sin(a + b)");
}

TEST(ExpressionFunctionsTests, cosTest) {
  EXPECT_EQ(cos(Expression("5*Pi")).toString(), "cos(5 Pi)");     // TODO trigonometry
  EXPECT_EQ(cos(Expression("3*Pi/2")).toString(), "cos(3/2 Pi)"); // TODO trigonometry
  EXPECT_EQ(cos(Expression("8*a")).toString(), "cos(8 a)");
}

TEST(ExpressionFunctionsTests, tanTest) {
  EXPECT_EQ(tan(Expression("0")).toString(), "0");
  EXPECT_EQ(tan(Expression("3*Pi/4")).toString(), "tan(3/4 Pi)"); // TODO trigonometry
  EXPECT_EQ(tan(Expression("a^3")).toString(), "tan(a^3)");
}

TEST(ExpressionFunctionsTests, cotTest) {
  EXPECT_EQ(cot(Expression("Pi/4")).toString(), "cot(1/4 Pi)"); // TODO trigonometry
  EXPECT_EQ(cot(Expression("Pi/2")).toString(), "cot(1/2 Pi)"); // TODO trigonometry
  EXPECT_EQ(cot(Expression("a/5")).toString(), "cot(1/5 a)");
}

TEST(ExpressionFunctionsTests, asinTest) {
  EXPECT_EQ(asin(Expression("0")).toString(), "0");
  EXPECT_EQ(asin(Expression("1")).toString(), "asin(1)"); // TODO trigonometry
  EXPECT_EQ(asin(Expression("a+b")).toString(), "asin(a + b)");
}

TEST(ExpressionFunctionsTests, acosTest) {
  EXPECT_EQ(acos(Expression("0")).toString(), "acos(0)"); // TODO trigonometry
  EXPECT_EQ(acos(Expression("1")).toString(), "0");
  EXPECT_EQ(acos(Expression("8*a")).toString(), "acos(8 a)");
}

TEST(ExpressionFunctionsTests, atanTest) {
  EXPECT_EQ(atan(Expression("0")).toString(), "0");
  EXPECT_EQ(atan(Expression("-1")).toString(), "atan(-1)"); // TODO trigonometry
  EXPECT_EQ(atan(Expression("a^3")).toString(), "atan(a^3)");
}

TEST(ExpressionFunctionsTests, acotTest) {
  EXPECT_EQ(acot(Expression("1")).toString(), "acot(1)"); // TODO trigonometry
  EXPECT_EQ(acot(Expression("0")).toString(), "acot(0)"); // TODO trigonometry
  EXPECT_EQ(acot(Expression("a/5")).toString(), "acot(1/5 a)");
}

TEST(ExpressionFunctionsTests, derivativeTest) {
  EXPECT_EQ(derivative(Expression("1")).toString(), "0");
  EXPECT_EQ(derivative(Expression("E")).toString(), "0");
  EXPECT_EQ(derivative(Expression("a")).toString(), "1");
  EXPECT_EQ(derivative(Expression("(a+5)")).toString(), "(a + 5)'"); // TODO: derivative
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

TEST(ExpressionFunctionsTests, solveTest) {
  EXPECT_EQ(solve(Expression("x - 10 = 0")).toString(), "x = 10");
  EXPECT_EQ(solve(Expression("x < -10")).toString(), "x < -10");
  EXPECT_EQ(solve(Expression("-10 - x = 0")).toString(), "x = -10");

  EXPECT_EQ(solve(Expression("x^2 - 10 = 39")).toString(), "x = -7 | x = 7");
  EXPECT_EQ(solve(Expression("x^2 = 0")).toString(), "x = 0");
  EXPECT_EQ(solve(Expression("x^2 = 1")).toString(), "x = -1 | x = 1");
  EXPECT_EQ(solve(Expression("x^2 = -1")).toString(), "x^2 + 1 = 0"); // TODO complex numbers
  EXPECT_EQ(solve(Expression("x^2 - 2x - 3 = 0")).toString(), "x = -1 | x = 3");
  EXPECT_EQ(solve(Expression("15 - 2x - x^2 = 0")).toString(), "x = -5 | x = 3");
  EXPECT_EQ(solve(Expression("x^2 + 12x + 36 = 0")).toString(), "x = -6");
  EXPECT_EQ(solve(Expression("x^2 + 12x = 0")).toString(), "x = -12 | x = 0");
  EXPECT_EQ(solve(Expression("x^2 - 23x - 3 = 0")).toString(), "x = -1/2 sqrt(541) + 23/2 | x = 1/2 sqrt(541) + 23/2");
  EXPECT_EQ(solve(Expression("-12x^2 - 23x + 30 = 0")).toString(),
            "x = -1/2 sqrt(1969/144) - 23/24 | x = 1/2 sqrt(1969/144) - 23/24");
  EXPECT_EQ(solve(Expression("-33x^2 - x + 34 = 0")).toString(),
            "x = -1/2 sqrt(4489/1089) - 1/66 | x = 1/2 sqrt(4489/1089) - 1/66");
  EXPECT_EQ(
      solve(Expression("2x^2 + 2sqrt(2)x + 1 = 0")).toString(),
      "x = -1/2 sqrt(sqrt(2)^2 - 2) - 1/2 sqrt(2) | x = 1/2 sqrt(sqrt(2)^2 - 2) - 1/2 sqrt(2)"); // TODO: x = -1/sqrt(2)

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

  EXPECT_EQ(solve(Expression("15x^2 + sin(25)x - 10% = Ey")).toString(), "x^2 + (sin(25) x)/15 - (E y)/15 - 1/150 = 0");
  EXPECT_EQ(solve(Expression("x + x_1 + x_2 + y + y_1 = 0")).toString(), "x + x_1 + x_2 + y + y_1 = 0");
}
