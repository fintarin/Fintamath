#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(ExpressionFunctionsTests, addTest) {
  EXPECT_EQ(add(Variable("a"), -1, Expression("b^2")).toString(), "b^2+a-1");
  EXPECT_EQ(add(10, Expression("a+2")).toString(), "a+12");
  EXPECT_EQ(add(Variable("a"), Expression("a+2")).toString(), "2*a+2");
  EXPECT_EQ(add(Expression("b+2"), Expression("a+2")).toString(), "a+b+4");
  EXPECT_EQ(add(Expression("10+a^3"), Expression("a^2")).toString(), "a^2+a^3+10"); // TODO sort powers
  EXPECT_EQ(add(Expression("a*b"), Expression("b*a")).toString(), "2*a*b");
  EXPECT_EQ(add(Expression("a+b"), Expression("a+b")).toString(), "2*a+2*b");
}

TEST(ExpressionFunctionsTests, mulTest) {
  EXPECT_EQ(mul(Variable("a"), -1, Expression("a*2")).toString(), "-2*a^2");
  EXPECT_EQ(mul(10, Expression("a+2")).toString(), "10*a+20");
  EXPECT_EQ(mul(Variable("a"), Expression("a^3+a^2")).toString(), "a^3+a^4");
  EXPECT_EQ(mul(5, Expression("a+3"), Expression("a+2")).toString(), "25*a+5*a^2+30"); // TODO: replace to 2*a^2+25*a+30
  EXPECT_EQ(mul(Expression("a+b"), Expression("3*b+c")).toString(),
            "3*a*b+3*b^2+a*c+b*c"); // TODO: replace to 3*b^2+3*a*b+a*c+b*c
}

TEST(ExpressionFunctionsTests, subTest) {
  EXPECT_EQ(sub(Variable("a"), Expression("b^2")).toString(), "-b^2+a");
  EXPECT_EQ(sub(10, Expression("a+2")).toString(), "-a+8");
  EXPECT_EQ(sub(Variable("a"), Expression("a+2")).toString(), "-2");
  EXPECT_EQ(sub(Expression("b+2"), Expression("a+2")).toString(), "-a+b");
  EXPECT_EQ(sub(Expression("10+a^3"), Expression("a^2")).toString(), "-a^2+a^3+10"); // TODO sort powers
  EXPECT_EQ(sub(Expression("a*b"), Expression("b*a")).toString(), "0");
  EXPECT_EQ(sub(Expression("a+b"), Expression("a+b")).toString(), "0");
}

TEST(ExpressionFunctionsTests, divTest) {
  EXPECT_EQ(div(Variable("a"), Expression("b^2")).toString(), "b^-2*a");
  EXPECT_EQ(div(10, Expression("a+2")).toString(), "10/(a+2)");
  EXPECT_EQ(div(Variable("a"), Expression("a+2")).toString(), "a/(a+2)");
  EXPECT_EQ(div(Expression("b+2"), Expression("a+2")).toString(), "(b+2)/(a+2)");
  EXPECT_EQ(div(Expression("10+a^3"), Expression("a^2")).toString(), "10*a^-2+a");
  EXPECT_EQ(div(Expression("a*b"), Expression("b*a")).toString(), "1");
  EXPECT_EQ(div(Expression("a+b"), Expression("a+b")).toString(), "1");
}

TEST(ExpressionFunctionsTests, eqvTest) {
  EXPECT_EQ(eqv(Expression("a+3"), Expression("3+a")).toString(), "true");
  EXPECT_EQ(eqv(Expression("a^2"), Expression("a*a+0")).toString(), "true");
}

TEST(ExpressionFunctionsTests, absTest) {
  EXPECT_EQ(abs(Expression("a+3")).toString(), "abs(a+3)");
  EXPECT_EQ(abs(Expression("a^4")).toString(), "abs(a^4)");
  EXPECT_EQ(abs(Expression("-333")).toString(), "333");
}

TEST(ExpressionFunctionsTests, factorialTest) {
  EXPECT_EQ(factorial(Expression("a+3")).toString(), "(a+3)!");
  EXPECT_EQ(factorial(Expression("a*3")).toString(), "(3*a)!");
  EXPECT_EQ(factorial(Expression("5")).toString(), "120");
}

TEST(ExpressionFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Expression("4")).toString(), "2");
  EXPECT_EQ(sqrt(Expression("5")).toString(), "sqrt(5)");
  // TODO: functions
  EXPECT_EQ(sqrt(Expression("a^4")).toString(), "sqrt(a^4)");
  EXPECT_EQ(sqrt(Expression("a^2*b*b")).toString(), "sqrt(a^2*b^2)");
  EXPECT_EQ(sqrt(Expression("a^2+b^2+2*a*b")).toString(), "sqrt(a^2+b^2+2*a*b)");
}

TEST(ExpressionFunctionsTests, powTest) {
  EXPECT_EQ(pow(Expression("a+b"), Expression("0")).toString(), "1");
  // TODO: functions
  //  EXPECT_EQ(pow(Expression("a^4"), Expression("a")).toString(), "a^(4*a)");
  //  EXPECT_EQ(pow(Expression("a^4"), Expression("2")).toString(), "a^8");
  //  EXPECT_EQ(pow(Expression("a*b"), Expression("a+3")).toString(), "a^a*a^3*b^a*b^3");
  EXPECT_EQ(pow(Expression("a+2"), Expression("2")).toString(), "a^2+4*a+4");
}

TEST(ExpressionFunctionsTests, expTest) {
  EXPECT_EQ(exp(Expression("a^4")).toString(), "exp(a^4)");
  EXPECT_EQ(exp(Expression("2")).toString(), "exp(2)");
  EXPECT_EQ(exp(Expression("0")).toString(), "1");
  EXPECT_EQ(exp(Expression("ln(5)")).toString(), "exp(ln(5))");
}

TEST(ExpressionFunctionsTests, logTest) {
  EXPECT_EQ(log(Expression("a+b"), Expression("1")).toString(), "log(a+b,1)");
  EXPECT_EQ(log(Expression("2*a"), Expression("a+b")).toString(), "log(2*a,a+b)");
  EXPECT_EQ(log(Expression("a"), Expression("a^5")).toString(), "log(a,a^5)"); // TODO logarithms
}

TEST(ExpressionFunctionsTests, lnTest) {
  EXPECT_EQ(ln(Expression("e*e")).toString(), "ln(e^2)"); // TODO logarithms
  EXPECT_EQ(ln(Expression("10")).toString(), "ln(10)");
}

TEST(ExpressionFunctionsTests, lbTest) {
  EXPECT_EQ(lb(Expression("1024*a")).toString(), "lb(1024*a)"); // TODO logarithms
  EXPECT_EQ(ln(Expression("2+a")).toString(), "ln(a+2)");       // TODO logarithms
}

TEST(ExpressionFunctionsTests, lgTest) {
  EXPECT_EQ(lg(Expression("10")).toString(), "1");
  EXPECT_EQ(lg(Expression("e*a")).toString(), "lg(a*e)");
}

TEST(ExpressionFunctionsTests, sinTest) {
  EXPECT_EQ(sin(Expression("5*pi")).toString(), "sin(5*pi)");   // TODO trigonometry
  EXPECT_EQ(sin(Expression("pi/2")).toString(), "sin(1/2*pi)"); // TODO trigonometry
  EXPECT_EQ(sin(Expression("a+b")).toString(), "sin(a+b)");
}

TEST(ExpressionFunctionsTests, cosTest) {
  EXPECT_EQ(cos(Expression("5*pi")).toString(), "cos(5*pi)");     // TODO trigonometry
  EXPECT_EQ(cos(Expression("3*pi/2")).toString(), "cos(3/2*pi)"); // TODO trigonometry
  EXPECT_EQ(cos(Expression("8*a")).toString(), "cos(8*a)");
}

TEST(ExpressionFunctionsTests, tanTest) {
  EXPECT_EQ(tan(Expression("0")).toString(), "0");
  EXPECT_EQ(tan(Expression("3*pi/4")).toString(), "tan(3/4*pi)"); // TODO trigonometry
  EXPECT_EQ(tan(Expression("a^3")).toString(), "tan(a^3)");
}

TEST(ExpressionFunctionsTests, cotTest) {
  EXPECT_EQ(cot(Expression("pi/4")).toString(), "cot(1/4*pi)"); // TODO trigonometry
  EXPECT_EQ(cot(Expression("pi/2")).toString(), "cot(1/2*pi)"); // TODO trigonometry
  EXPECT_EQ(cot(Expression("a/5")).toString(), "cot(1/5*a)");
}

TEST(ExpressionFunctionsTests, asinTest) {
  EXPECT_EQ(asin(Expression("0")).toString(), "0");
  EXPECT_EQ(asin(Expression("1")).toString(), "asin(1)"); // TODO trigonometry
  EXPECT_EQ(asin(Expression("a+b")).toString(), "asin(a+b)");
}

TEST(ExpressionFunctionsTests, acosTest) {
  EXPECT_EQ(acos(Expression("0")).toString(), "acos(0)"); // TODO trigonometry
  EXPECT_EQ(acos(Expression("1")).toString(), "0");
  EXPECT_EQ(acos(Expression("8*a")).toString(), "acos(8*a)");
}

TEST(ExpressionFunctionsTests, atanTest) {
  EXPECT_EQ(atan(Expression("0")).toString(), "0");
  EXPECT_EQ(atan(Expression("-1")).toString(), "atan(-1)"); // TODO trigonometry
  EXPECT_EQ(atan(Expression("a^3")).toString(), "atan(a^3)");
}

TEST(ExpressionFunctionsTests, acotTest) {
  EXPECT_EQ(acot(Expression("1")).toString(), "acot(1)"); // TODO trigonometry
  EXPECT_EQ(acot(Expression("0")).toString(), "acot(0)"); // TODO trigonometry
  EXPECT_EQ(acot(Expression("a/5")).toString(), "acot(1/5*a)");
}