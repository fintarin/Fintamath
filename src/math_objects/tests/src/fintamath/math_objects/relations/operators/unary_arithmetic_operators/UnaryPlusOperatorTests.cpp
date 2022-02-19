#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryPlusOperator.hpp"

using namespace fintamath;

const UnaryPlusOperator oper;

TEST(UnaryPlusOperatorTests, callOperatorTest) {
  EXPECT_EQ(*oper({std::make_unique<Integer>(20)}).at(0), Integer(20));
  EXPECT_EQ(*oper({std::make_unique<Rational>(2, 3)}).at(0), Rational(2, 3));

  auto s = std::make_shared<Set>();
  EXPECT_THROW(oper({s}), std::invalid_argument);
}

TEST(UnaryPlusOperatorTests, intCallOperatorTest) {
  EXPECT_EQ(*oper(Integer(4574234)), Integer(4574234));
}

TEST(UnaryPlusOperatorTests, ratCallOperatorTest) {
  EXPECT_EQ(*oper(Rational(4574234, 48483532)), Rational(4574234, 48483532));
}

TEST(UnaryPlusOperatorTests, toStringTest) {
  EXPECT_EQ(oper.toString(), "+");
}
