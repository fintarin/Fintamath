#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMinusOperator.hpp"

using namespace fintamath;

const BinaryMinusOperator oper;

TEST(BinaryMinusOperatorTests, callOperatorTest) {
  EXPECT_EQ(*oper({std::make_unique<Integer>(20), std::make_unique<Integer>(10)}).at(0), Integer(10));
  EXPECT_EQ(*oper({std::make_unique<Rational>(2, 3), std::make_unique<Rational>(3, 4)}).at(0), Rational(-1, 12));
  EXPECT_EQ(*oper({std::make_unique<Integer>(20), std::make_unique<Rational>(3, 4)}).at(0), Rational(77, 4));
  EXPECT_EQ(*oper({std::make_unique<Rational>(2, 3), std::make_unique<Integer>(10)}).at(0), Rational(-28, 3));

  auto s = std::make_shared<Set>();
  EXPECT_THROW(oper({s, s}), std::invalid_argument);
}

TEST(BinaryMinusOperatorTests, intIntCallOperatorTest) {
  EXPECT_EQ(*oper(Integer("923749326428379569328756"), Integer("437826432987462398746289734")),
            Integer("-436902683661034019176960978"));
}

TEST(BinaryMinusOperatorTests, ratRatCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(4574234, 48483532), Rational(3445466, 1)), Rational(-83524178245839, 24241766));
  EXPECT_EQ(*oper(Rational(3, 4), Rational(6, 8)), Integer(0));
}

TEST(BinaryMinusOperatorTests, intRatCallOperatorTest) {
  EXPECT_EQ(*oper(Integer(54532), Rational(3898765, 4234982374)), Rational(230942054920203, 4234982374));
}

TEST(BinaryMinusOperatorTests, ratIntCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(253536, 3091327), Integer(10238947)), Rational(-31651933059133, 3091327));
}

TEST(BinaryMinusOperatorTests, toStringTest) {
  EXPECT_EQ(oper.toString(), "-");
}
