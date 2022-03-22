#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryPlus.hpp"

using namespace fintamath;

const UnaryPlus oper;

TEST(UnaryPlusTests, callOperatorTest) {
  EXPECT_EQ(*oper({std::make_shared<Integer>(20)}), Integer(20));
  EXPECT_EQ(*oper({std::make_shared<Rational>(2, 3)}), Rational(2, 3));

  EXPECT_NE(*oper({std::make_shared<Integer>(20)}), Integer(21));
  EXPECT_NE(*oper({std::make_shared<Rational>(2, 3)}), Rational(2, 5));

  auto s = std::make_shared<Set>();
  EXPECT_THROW(oper({s}), std::invalid_argument);

  EXPECT_THROW(oper(Set{}), std::invalid_argument);
  EXPECT_THROW(oper({std::make_shared<Integer>(20), std::make_shared<Integer>(20)}), std::invalid_argument);
}

TEST(UnaryPlusTests, intCallOperatorTest) {
  EXPECT_EQ(*oper(Integer(4574234)), Integer(4574234));
}

TEST(UnaryPlusTests, ratCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(4574234, 48483532)), Rational(4574234, 48483532));
}

TEST(UnaryPlusTests, toStringTest) {
  EXPECT_EQ(oper.toString(), "+");
}
