#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionComparator.hpp"

using namespace fintamath;

TEST(ExpressionComparatorTests, comparatorTest) {
  EXPECT_EQ(compare(Variable("a").clone(), Expression("a").clone()), std::strong_ordering::equal);
  EXPECT_EQ(compare(Expression("a").clone(), Expression("a").clone()), std::strong_ordering::equal);
  EXPECT_EQ(compare(Integer(2).clone(), Expression("2 a").clone()), std::strong_ordering::less);
  EXPECT_EQ(compare(Integer(2).clone(), Expression("2 a").clone()), std::strong_ordering::less);
  EXPECT_EQ(compare(Variable("a").clone(), Expression("a b").clone()), std::strong_ordering::less);
  EXPECT_EQ(compare(Variable("a").clone(), Expression("a + b").clone()), std::strong_ordering::less);
  EXPECT_EQ(compare(Expression("a^b").clone(), Expression("a b c").clone()), std::strong_ordering::greater);

  // TODO: add more tests
}
