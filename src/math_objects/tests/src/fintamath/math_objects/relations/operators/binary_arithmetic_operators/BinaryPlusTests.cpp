#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryPlus.hpp"

using namespace fintamath;

const BinaryPlus oper;

TEST(BinaryPlusTests, callOperatorTest) {
  EXPECT_EQ(*oper({std::make_shared<Integer>(20), std::make_shared<Integer>(10)}).at(0), Integer(30));
  EXPECT_EQ(*oper({std::make_shared<Rational>(2, 3), std::make_shared<Rational>(3, 4)}).at(0), Rational(17, 12));
  EXPECT_EQ(*oper({std::make_shared<Integer>(21), std::make_shared<Rational>(3, 4)}).at(0), Rational(87, 4));
  EXPECT_EQ(*oper({std::make_shared<Rational>(2, 3), std::make_shared<Integer>(10)}).at(0), Rational(32, 3));

  auto s = std::make_shared<Set>();
  EXPECT_THROW(oper({s, s}), std::invalid_argument);
}

TEST(BinaryPlusTests, intIntCallOperatorTest) {
  EXPECT_EQ(*oper(Integer("923749326428379569328756"), Integer("437826432987462398746289734")),
            Integer("438750182313890778315618490"));
}

TEST(BinaryPlusTests, ratRatCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(656, 434), Rational(5356, 2424200)), Rational(6421773, 4242350));
  EXPECT_EQ(*oper(Rational(2, 3), Rational(1, 3)), Integer(1));
}

TEST(BinaryPlusTests, intRatCallOperatorTest) {
  EXPECT_EQ(*oper(Integer(33), Rational(34, 77)), Rational(2575, 77));
}

TEST(BinaryPlusTests, ratIntCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(546, 23), Integer(25)), Rational(1121, 23));
}

TEST(BinaryPlusTests, toStringTest) {
  EXPECT_EQ(oper.toString(), "+");
}
