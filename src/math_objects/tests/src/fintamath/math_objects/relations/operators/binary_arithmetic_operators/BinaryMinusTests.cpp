#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMinus.hpp"

using namespace fintamath;

const BinaryMinus oper;

TEST(BinaryMinusTests, callOperatorTest) {
  EXPECT_EQ(*oper({std::make_shared<Integer>(20), std::make_shared<Integer>(10)}).at(0), Integer(10));
  EXPECT_EQ(*oper({std::make_shared<Rational>(2, 3), std::make_shared<Rational>(3, 4)}).at(0), Rational(-1, 12));
  EXPECT_EQ(*oper({std::make_shared<Integer>(20), std::make_shared<Rational>(3, 4)}).at(0), Rational(77, 4));
  EXPECT_EQ(*oper({std::make_shared<Rational>(2, 3), std::make_shared<Integer>(10)}).at(0), Rational(-28, 3));

  auto s = std::make_shared<Set>();
  EXPECT_THROW(oper({s, s}), std::invalid_argument);
}

TEST(BinaryMinusTests, intIntCallOperatorTest) {
  EXPECT_EQ(*oper(Integer("923749326428379569328756"), Integer("437826432987462398746289734")),
            Integer("-436902683661034019176960978"));
}

TEST(BinaryMinusTests, ratRatCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(4574234, 48483532), Rational(3445466, 1)), Rational(-83524178245839, 24241766));
  EXPECT_EQ(*oper(Rational(3, 4), Rational(6, 8)), Integer(0));
}

TEST(BinaryMinusTests, intRatCallOperatorTest) {
  EXPECT_EQ(*oper(Integer(54532), Rational(3898765, 4234982374)), Rational(230942054920203, 4234982374));
}

TEST(BinaryMinusTests, ratIntCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(253536, 3091327), Integer(10238947)), Rational(-31651933059133, 3091327));
}

TEST(BinaryMinusTests, toStringTest) {
  EXPECT_EQ(oper.toString(), "-");
}
