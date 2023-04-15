#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(FintamathTests, fintamathTests) {
  Expression expr;

  expr = sum(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "a + b + E + Pi");

  expr = mul(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "E Pi a b");

  expr = pow(Variable("a"), Variable("b")) * Variable("c");
  EXPECT_EQ(expr.toString(), "a^b c");

  // TODO trigonometry
  // expr = pow(sin(Variable("x")), 2) + pow(cos(Variable("x")), 2);
  // EXPECT_EQ(expr.toString(), "1");
  // expr = pow(sin(Expression(2)), 2) + pow(cos(Expression(2)), 2);
  // EXPECT_EQ(expr.toString(), "1");

  Expression x("x");
  Expression y("y");

  expr = eqv(x * x + y * y * y, x * y);

  EXPECT_EQ(expr.toString(), "x^2 - x y + y^3 = 0");

  expr = eqv(x * x + y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2 - x y + y^2 = 0");

  expr = eqv(pow(x, 2) - 10, 39);
  EXPECT_EQ(solve(expr).toString(), "x = -7 | x = 7");

  expr = Expression("-3x^2 + 28x - 49 = 0");
  EXPECT_EQ(solve(expr).precise(2).toString(), "x = 2.3 | x = 7");

  expr = Expression("-4x^2 + 28x - 49 = 0");
  EXPECT_EQ(solve(expr).precise(2).toString(), "x = 3.5");

  expr = Expression("-4x^2 + 28x - 49 = 0");
  EXPECT_EQ(solve(expr).toString(), "x = 7/2");

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
