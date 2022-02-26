#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryMultiply.hpp"

using namespace fintamath;

const BinaryMultiply oper;

TEST(BinaryMultiplyTests, callOperatorTest) {
  EXPECT_EQ(*oper({std::make_shared<Integer>(20), std::make_shared<Integer>(10)}).at(0), Integer(200));
  EXPECT_EQ(*oper({std::make_shared<Rational>(2, 3), std::make_shared<Rational>(3, 4)}).at(0), Rational(1, 2));
  EXPECT_EQ(*oper({std::make_shared<Integer>(21), std::make_shared<Rational>(3, 4)}).at(0), Rational(63, 4));
  EXPECT_EQ(*oper({std::make_shared<Rational>(2, 3), std::make_shared<Integer>(10)}).at(0), Rational(20, 3));

  auto s = std::make_shared<Set>();
  EXPECT_THROW(oper({s, s}), std::invalid_argument);
}

TEST(BinaryMultiplyTests, intIntCallOperatorTest) {
  EXPECT_EQ(*oper(Integer("923749326428379569328756"), Integer("437826432987462398746289734")),
            Integer("404441872564708456096142978365087208962279873790904"));
}

TEST(BinaryMultiplyTests, ratRatCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(5464, 42424), Rational(854320, 34344265575)), Rational(116700112, 36425528068845));
  EXPECT_EQ(*oper(Rational(20, 3), Rational(3, 4)), Integer(5));
}

TEST(BinaryMultiplyTests, intRatCallOperatorTest) {
  EXPECT_EQ(*oper(Integer(6584), Rational(9247, 42323)), Rational(60882248, 42323));
}

TEST(BinaryMultiplyTests, ratIntCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(2355852, 343434), Integer(20000)), Rational(7852840000, 57239));
}

TEST(BinaryMultiplyTests, toStringTest) {
  EXPECT_EQ(oper.toString(), "*");
}

TEST(BinaryMultiplyTests, getPriorityTest) {
  EXPECT_EQ(oper.getPriority(), 2);
}
