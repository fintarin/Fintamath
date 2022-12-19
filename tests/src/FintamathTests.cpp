#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/Functions.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(FintamathTests, fintamathTests) {
  Expression expr;

  expr = add(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "a+b+e+pi");

  expr = mul(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "a*b*e*pi");

  expr = pow(Variable("a"), Variable("b")) * Variable("c");
  EXPECT_EQ(expr.toString(), "a^b*c");

  expr = pow(Variable("a"), Variable("b")) * Variable("c");
  EXPECT_EQ(expr.toString(), "a^b*c");

  //expr = pow(sin(Expression(2)), 2) + pow(cos(Expression(2)), 2);
  //EXPECT_EQ(expr.toString(), "1");

  // TODO trigonometry
  // expr = pow(sin(Variable("x")), 2) + pow(cos(Variable("x")), 2);
  // EXPECT_EQ(expr.toString(), "1");

  Expression x("x");
  Expression y("y");

  expr = eqv(x * x + y * y * y, x * y);

  //TODO: replace to y^3+x^2-x*y=0
  EXPECT_EQ(expr.toString(), "x^2+y^3-x*y=0");

  expr = eqv(x * x + y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2+y^2-x*y=0");

  expr = eqv(pow(x, 2) - 10, 39);
  EXPECT_EQ(expr.solve(), "x in {-7,7}");

  expr = Expression("-4x^2 + 28x - 49 = 0");
  EXPECT_EQ(expr.solve(2), "x in {3.5}");

  expr = Expression("-4x^2 + 28x - 49 = 0");
  EXPECT_EQ(expr.solve(), "x in {7/2}");

  expr = Expression("sin2^2 + cos2^2 = 1");
  EXPECT_EQ(expr.solve(), "true");

  //EXPECT_ANY_THROW(1 / (ln(pow(e(), pow(e(), e()))) - pow(e(), e())));
  //EXPECT_ANY_THROW(1 / (ln(ln(pow(e(), pow(e(), e())))) - e()));

  EXPECT_ANY_THROW(1 / (pow(sin(Real(2)), 2) + pow(cos(Real(2)), 2) - 1));
  EXPECT_ANY_THROW(1 / (tan(Real(2)) * cot(Real(2)) - 1));
}
