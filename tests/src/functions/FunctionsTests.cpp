#include <gtest/gtest.h>

#include "fintamath/functions/Functions.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;


//TEST(FunctionsTests, addTest) {
//  EXPECT_EQ(add(Variable("a"), -1, Expression("b^2")).toString(), "b^2+a-1");
//  EXPECT_EQ(add(10, Expression("a+2")).toString(), "a+12");
//  EXPECT_EQ(add(Variable("a"), Expression("a+2")).toString(), "2*a+2");
//  EXPECT_EQ(add(Expression("b+2"), Expression("a+2")).toString(), "a+b+4");
//  EXPECT_EQ(add(Expression("10+a^3"), Expression("a^2")).toString(), "a^3+a^2+10");
//  EXPECT_EQ(add(Expression("a*b"), Expression("b*a")).toString(), "2*a*b");
//  EXPECT_EQ(add(Expression("a+b"), Expression("a+b")).toString(), "2*a+2*b");
//}
//
//TEST(FunctionsTests, mulTest) {
//    EXPECT_EQ(mul(Variable("a"), -1, Expression("a*2")).toString(), "-2*a^2");
//    EXPECT_EQ(mul(10, Expression("a+2")).toString(), "20*a+20");
//    EXPECT_EQ(mul(Variable("a"), Expression("a^3+a^2")).toString(), "a^4+a^3");
//    EXPECT_EQ(mul(5, Expression("a+3"), Expression("a+2")).toString(), "2*a^2+25*a+30");
//    EXPECT_EQ(mul(Expression("a+b"), Expression("3*b+c")).toString(), "3*b^2+3*a*b+a*c+b*c");
//}
//
//TEST(FunctionsTests, eqvTest) {
//  EXPECT_EQ(eqv(Expression("a+3"), Expression("3+a")).toString(), "true");
//  EXPECT_EQ(eqv(Expression("a^2"), Expression("a*a+0")).toString(), "true");
//}
//
//TEST(FunctionsTests, absTest) {
//  EXPECT_EQ(abs(Expression("a+3")).toString(), "abs(a+3)");
//  EXPECT_EQ(abs(Expression("a^4")).toString(), "a^4");
//  EXPECT_EQ(abs(Expression("-333")).toString(), "333");
//}
//
//TEST(FunctionsTests, factorialTest) {
//  EXPECT_EQ(factorial(Expression("a+3")).toString(), "(a+3)!");
//  EXPECT_EQ(factorial(Expression("a*3")).toString(), "(3*a)!");
//  EXPECT_EQ(factorial(Expression("5")).toString(), "120");
//}
//
//TEST(FunctionsTests, doubleFactorialTest) {
//  EXPECT_EQ(doubleFactorial(Expression("a+3")).toString(), "(a+3)!!");
//  EXPECT_EQ(doubleFactorial(Expression("a*3")).toString(), "(3*a)!!");
//  EXPECT_EQ(doubleFactorial(Expression("5")).toString(), "15");
//}
//
//TEST(FunctionsTests, sqrtTest) {
//  EXPECT_EQ(doubleFactorial(Expression("a^4")).toString(), "a^2");
//  EXPECT_EQ(doubleFactorial(Expression("a^2*b*b")).toString(), "a*b");
//  EXPECT_EQ(doubleFactorial(Expression("a^2+b^2+2*a*b")).toString(), "a+b");
//  EXPECT_EQ(doubleFactorial(Expression("16*b*a^2")).toString(), "4*a*sqrt(b)");
//  EXPECT_EQ(doubleFactorial(Expression("a*3")).toString(), "sqrt(3*a)");
//  EXPECT_EQ(doubleFactorial(Expression("16")).toString(), "4");
//}
//
//TEST(FunctionsTests, powTest) {
//  EXPECT_EQ(pow(Expression("a+b"), Expression("0")).toString(), "1");
//  EXPECT_EQ(pow(Expression("a^4"), Expression("a")).toString(), "a^(4*a)");
//  EXPECT_EQ(pow(Expression("a^4"), Expression("2")).toString(), "a^8");
//  EXPECT_EQ(pow(Expression("a+2"), Expression("2")).toString(), "a^2+4*a+4");
//  EXPECT_EQ(pow(Expression("a*b"), Expression("a+3")).toString(), "a^a*a^3*b^a*b^3");
//}
//
//TEST(FunctionsTests, expTest) {
//  EXPECT_EQ(exp(Expression("a^4")).toString(), "exp(a^4)");
//  EXPECT_EQ(exp(Expression("2")).toString(), "exp(2)");
//  EXPECT_EQ(exp(Expression("0")).toString(), "1");
//  EXPECT_EQ(exp(Expression("ln(5)")).toString(), "5");
//}
//
//TEST(FunctionsTests, logTest) {
//  EXPECT_EQ(log(Expression("a+b"), Expression("1")).toString(), "0");
//  EXPECT_EQ(log(Expression("2*a"), Expression("a+b")).toString(), "log(2*a, a+b)");
//  EXPECT_EQ(log(Expression("a"), Expression("a^5")).toString(), "5");
//}
//
//TEST(FunctionsTests, lnTest) {
//  EXPECT_EQ(ln(Expression("e*e")).toString(), "2");
//  EXPECT_EQ(ln(Expression("10")).toString(), "ln(10)");
//}
//
//TEST(FunctionsTests, lbTest) {
//  EXPECT_EQ(lb(Expression("1024*a")).toString(), "10*lb(a)");
//  EXPECT_EQ(ln(Expression("2+a")).toString(), "lb(2+a)");
//}
//
//TEST(FunctionsTests, lgTest) {
//  EXPECT_EQ(lg(Expression("10")).toString(), "1");
//  EXPECT_EQ(lg(Expression("e*a")).toString(), "lg(e)+lg(a)");
//}
//
//TEST(FunctionsTests, sinTest) {
//  EXPECT_EQ(sin(Expression("5*pi")).toString(), "0");
//  EXPECT_EQ(sin(Expression("pi/2")).toString(), "1");
//  EXPECT_EQ(sin(Expression("a+b")).toString(), "sin(a+b)");
//}
//
//TEST(FunctionsTests, cosTest) {
//  EXPECT_EQ(cos(Expression("5*pi")).toString(), "-1");
//  EXPECT_EQ(cos(Expression("3*pi/2")).toString(), "0");
//  EXPECT_EQ(cos(Expression("8*a")).toString(), "cos(8*a)");
//}
//
//TEST(FunctionsTests, tanTest) {
//  EXPECT_EQ(tan(Expression("0")).toString(), "0");
//  EXPECT_EQ(tan(Expression("3*pi/4")).toString(), "-1");
//  EXPECT_EQ(tan(Expression("a^3")).toString(), "tan(a^3)");
//}
//
//TEST(FunctionsTests, cotTest) {
//  EXPECT_EQ(cot(Expression("pi/4")).toString(), "1");
//  EXPECT_EQ(cot(Expression("pi/2")).toString(), "0");
//  EXPECT_EQ(cot(Expression("a/5")).toString(), "cot(a/5)");
//
//}
//
//TEST(FunctionsTests, asinTest) {
//  EXPECT_EQ(asin(Expression("0")).toString(), "0");
//  EXPECT_EQ(asin(Expression("1")).toString(), "pi/2");
//  EXPECT_EQ(asin(Expression("a+b")).toString(), "asin(a+b)");
//}
//
//TEST(FunctionsTests, acosTest) {
//  EXPECT_EQ(acos(Expression("0")).toString(), "pi/2");
//  EXPECT_EQ(acos(Expression("1")).toString(), "0");
//  EXPECT_EQ(acos(Expression("8*a")).toString(), "acos(8*a)");
//}
//
//TEST(FunctionsTests, atanTest) {
//  EXPECT_EQ(atan(Expression("0")).toString(), "0");
//  EXPECT_EQ(atan(Expression("-1")).toString(), "-1*pi/4");
//  EXPECT_EQ(atan(Expression("a^3")).toString(), "atan(a^3)");
//
//}
//
//TEST(FunctionsTests, acotTest) {
//  EXPECT_EQ(acot(Expression("1")).toString(), "pi/4");
//  EXPECT_EQ(acot(Expression("0")).toString(), "pi/2");
//  EXPECT_EQ(acot(Expression("a/5")).toString(), "acot(a/5)");
//}