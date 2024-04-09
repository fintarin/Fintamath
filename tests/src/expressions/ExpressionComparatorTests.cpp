#include <gtest/gtest.h>

#include "fintamath/expressions/ExpressionComparator.hpp"

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;
using namespace detail;

TEST(ExpressionComparatorTests, comparatorTest) {
  EXPECT_EQ(compare({}, {}), std::strong_ordering::equal);
  EXPECT_EQ(compare({}, Integer(2).clone()), std::strong_ordering::less);
  EXPECT_EQ(compare(Integer(2).clone(), {}), std::strong_ordering::greater);

  EXPECT_EQ(compare(Integer(2).clone(), Integer(2).clone()), std::strong_ordering::equal);
  EXPECT_EQ(compare(Integer(2).clone(), Expression(2).clone()), std::strong_ordering::equal);
  EXPECT_EQ(compare(Integer(2).clone(), Expression("2 a").clone()), std::strong_ordering::less);

  EXPECT_EQ(compare(Variable("a").clone(), Variable("a").clone()), std::strong_ordering::equal);
  EXPECT_EQ(compare(Variable("a").clone(), Expression("a").clone()), std::strong_ordering::equal);
  EXPECT_EQ(compare(Variable("a").clone(), Expression("a b").clone()), std::strong_ordering::less);
  EXPECT_EQ(compare(Variable("a").clone(), Expression("a + b").clone()), std::strong_ordering::less);

  EXPECT_EQ(compare(Expression("a").clone(), Expression("a").clone()), std::strong_ordering::equal);
  EXPECT_EQ(compare(Expression("a^b").clone(), Expression("a b c").clone()), std::strong_ordering::greater);
  EXPECT_EQ(compare(Expression("x^x").clone(), Expression("x^y").clone()), std::strong_ordering::greater);

  EXPECT_EQ(compare(parseRawExpr("sqrt(11)"), parseRawExpr("root(2022369065670411386760301914510907000742418, 4)")), std::strong_ordering::greater);
  EXPECT_EQ(compare(parseRawExpr("x^x ln(x)"), parseRawExpr("x^x")), std::strong_ordering::greater);
  EXPECT_EQ(compare(parseRawExpr("~a & c"), parseRawExpr("a & b & ~c")), std::strong_ordering::greater);

  EXPECT_EQ(compare(parseRawExpr("x"), parseRawExpr("ln(x)"), {.termOrderInversed = false}), std::strong_ordering::less);
  EXPECT_EQ(compare(parseRawExpr("x"), parseRawExpr("ln(x)"), {.termOrderInversed = true}), std::strong_ordering::greater);
}