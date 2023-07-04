#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(FintamathTests, fintamathTests) {
  Expression expr;

  expr = add(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "a + b + E + Pi");

  expr = mul(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "E Pi a b");

  expr = pow(Variable("a"), Variable("b")) * Variable("c");
  EXPECT_EQ(expr.toString(), "a^b c");

  Variable x("x");
  Variable y("y");

  // TODO: sin^2(x) + cos^2(x) & tan(x) * cot(x)
  // expr = pow(sin(x), 2) + pow(cos(x), 2) + tan(x) * cot(x);
  // EXPECT_EQ(expr.toString(), "2");

  // TODO: trigonometric constants simplify
  // expr = sin(asin(x)) + sin(Expression("-3Pi/2")) + cos(Expression("Pi/4"));
  // EXPECT_EQ(expr.toString(), "x + 1/sqrt(2) + 1");

  expr = log(2, 256) + ln(pow(E(), 2));
  EXPECT_EQ(expr.toString(), "10");

  expr = sqrt(Expression(8));
  EXPECT_EQ(expr.toString(), "2 sqrt(2)");

  expr = pow(Expression("244706656946119777797996531655819747089832578"), Rational(1, 4));
  EXPECT_EQ(expr.toString(), "root(2022369065670411386760301914510907000742418, 4) sqrt(11)");

  expr = Expression("(4x^4 + 1 + 3x^3 + 2x) / (x^2 + x + 2)");
  EXPECT_EQ(expr.toString(), "4 x^2 - x - 7 + (11 x + 15)/(x^2 + x + 2)");

  expr = x * x * x * y + 10 * x;
  EXPECT_EQ(expr.toString(), "x^3 y + 10 x");

  expr = x + 10 * x / 10 + (sqrt(x) * 2);
  EXPECT_EQ(expr.toString(), "2 sqrt(x) + 2 x");

  expr = eqv(x * x + y * y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2 - x y + y^3 = 0");

  expr = eqv(x * x + y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2 - x y + y^2 = 0");

  expr = eqv(x / x - y / y, x / y);
  EXPECT_EQ(expr.toString(), "x/y = 0");

  expr = eqv(pow(x, 2) - 10, 39);
  EXPECT_EQ(solve(expr).toString(), "x = -7 | x = 7");

  expr = Expression("-4x^2 + 28x - 49 = 0");
  EXPECT_EQ(solve(expr).toString(), "x = 7/2");

  // TODO: cubic equations and complex numbers
  // expr = Expression("x^3 + x^2 + x + 1 = 0");
  // EXPECT_EQ(solve(expr).toString(), "x = -I | x = I | x = -1");

  // TODO: quadratic inequations
  // expr = Expression("x^2 + x - 1 < 0");
  // EXPECT_EQ(solve(expr).toString(), "x > -sqrt(2) - 1 & x < sqrt(2) - 1");

  expr = Expression("-3x^2 + 28x - 49 = 0");
  EXPECT_EQ(solve(expr).precise(2).toString(), "x = 2.3 | x = 7");

  // TODO: derivative
  // expr = derivative(sin(pow(x, 2)) + cos(pow(x, 3)), x);
  // EXPECT_EQ(expr.toString(), "2 x cos(x^2) - 3 x^2 sin(x^3)");

  // TODO: integral
  // expr = integral(2 * pow(x, 2) + 10 / x, x);
  // EXPECT_EQ(expr.toString(), "(2 x^3)/3 + 10 ln(x)");

  expr = Expression("~a & b | ~c -> a <-> b !<-> c");
  EXPECT_EQ(expr.toString(), "(a & b & ~c) | (~a & ~b & ~c) | (~a & c) | (~b & c)");

  {
    Expression expr1("(x+1)^6");
    EXPECT_EQ(expr1.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");

    Expression expr2 = solve(expr1);
    EXPECT_EQ(expr2.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");

    Expression expr3 = expr2.precise(10);
    EXPECT_EQ(expr3.toString(), "x^6 + 6 x^5 + 15 x^4 + 20 x^3 + 15 x^2 + 6 x + 1");
  }

  {
    Expression expr1("(x+1)^7");
    EXPECT_EQ(expr1.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");

    Expression expr2 = solve(expr1);
    EXPECT_EQ(expr2.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");

    Expression expr3 = expr2.precise(10);
    EXPECT_EQ(expr3.toString(), "x^7 + 7 x^6 + 21 x^5 + 35 x^4 + 35 x^3 + 21 x^2 + 7 x + 1");
  }

  // TODO trigonometry
  // expr = Expression("sin2^2 + cos2^2 = 1");
  // EXPECT_EQ(solve(expr).toString(), "True");

  // TODO: function minimization
  // EXPECT_ANY_THROW(1 / (ln(pow(e(), pow(e(), e()))) - pow(e(), e())));
  // EXPECT_ANY_THROW(1 / (ln(ln(pow(e(), pow(e(), e())))) - e()));

  // TODO: function minimization
  // EXPECT_ANY_THROW(1 / (pow(sin(Real(2)), 2) + pow(cos(Real(2)), 2) - 1));
  // EXPECT_ANY_THROW(1 / (tan(Real(2)) * cot(Real(2)) - 1));
}
