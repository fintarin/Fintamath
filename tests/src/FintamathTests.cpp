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
  Variable x("x");
  Variable y("y");

  //-------------------------------------------------------------------------------------//

  expr = add(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "a + b + E + Pi");

  expr = mul(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "E Pi a b");

  expr = pow(Variable("a"), Variable("b")) * Variable("c");
  EXPECT_EQ(expr.toString(), "a^b c");

  expr = x * x * x * y + 10 * x;
  EXPECT_EQ(expr.toString(), "x^3 y + 10 x");

  expr = x + 10 * x / 10 + (sqrt(x) * 2);
  EXPECT_EQ(expr.toString(), "2 x + 2 sqrt(x)");

  expr = eqv(x * x + y * y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2 - x y + y^3 = 0");

  expr = eqv(x * x + y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2 - x y + y^2 = 0");

  expr = eqv(x / x - y / y, x / y);
  EXPECT_EQ(expr.toString(), "x = 0");

  expr = Expression("(4x^4 + 1 + 3x^3 + 2x) / (x^2 + x + 2)");
  EXPECT_EQ(expr.toString(), "4 x^2 - x - 7 + (11 x + 15)/(x^2 + x + 2)");

  expr = log(2, 256) + ln(pow(e(), 2));
  EXPECT_EQ(expr.toString(), "10");

  expr = sqrt(Expression(8));
  EXPECT_EQ(expr.toString(), "2 sqrt(2)");

  expr = pow(Expression("244706656946119777797996531655819747089832578"), Rational(1, 4));
  EXPECT_EQ(expr.toString(), "sqrt(11) root(2022369065670411386760301914510907000742418, 4)");

  expr = sin(asin(Variable(x))) + cos(acos(Integer(1)));
  EXPECT_EQ(expr.toString(), "x + 1");

  expr = Expression("~a & b | ~c -> a <-> b !<-> c");
  EXPECT_EQ(expr.toString(), "(a & b & ~c) | (~a & ~b & ~c) | (~a & c) | (~b & c)");

  //-------------------------------------------------------------------------------------//

  expr = eqv(pow(x, 2) - 10, 39);
  EXPECT_EQ(solve(expr).toString(), "x = -7 | x = 7");

  expr = Expression("-4x^2 + 28x - 49 = 0");
  EXPECT_EQ(solve(expr).toString(), "x = 7/2");

  expr = Expression("-3x^2 + 28x - 49 = 0");
  EXPECT_EQ(solve(expr).precise(2).toString(), "x = 2.3 | x = 7.0");
}
