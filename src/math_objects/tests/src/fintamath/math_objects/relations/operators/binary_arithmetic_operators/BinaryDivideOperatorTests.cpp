#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryDivideOperator.hpp"

using namespace fintamath;

const BinaryDivideOperator oper;

TEST(BinaryDivideOperatorTests, callOperatorTest) {
  EXPECT_EQ(*oper({std::make_unique<Integer>(20), std::make_unique<Integer>(10)}).at(0), Integer(2));
  EXPECT_EQ(*oper({std::make_unique<Rational>(2, 3), std::make_unique<Rational>(3, 4)}).at(0), Rational(8, 9));
  EXPECT_EQ(*oper({std::make_unique<Integer>(20), std::make_unique<Rational>(3, 4)}).at(0), Rational(80, 3));
  EXPECT_EQ(*oper({std::make_unique<Rational>(2, 3), std::make_unique<Integer>(10)}).at(0), Rational(1, 15));

  auto s = std::make_shared<Set>();
  EXPECT_THROW(oper({s, s}), std::invalid_argument);
}

TEST(BinaryDivideOperatorTests, intIntCallOperatorTest) {
  EXPECT_EQ(*oper(Integer("437826432987462398746289734"), Integer("923749326428379569328756")), Integer(473));
}

TEST(BinaryDivideOperatorTests, ratRatCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(9825742, 532437), Rational(3445466, 100000000)), Rational(491287100000000, 917246790321));
  EXPECT_EQ(*oper(Rational(3, 4), Rational(6, 8)), Integer(1));
}

TEST(BinaryDivideOperatorTests, intRatCallOperatorTest) {
  EXPECT_EQ(*oper(Integer(123083500), Rational(90193108, 13094120)), Rational(402917529755000, 22548277));
}

TEST(BinaryDivideOperatorTests, ratIntCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(100000, 10000000), Integer(87539235335)), Rational(1, 8753923533500));
}

TEST(BinaryDivideOperatorTests, toStringTest) {
  EXPECT_EQ(oper.toString(), "/");
}
