#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryArithmeticOperatorParser.hpp"

using namespace fintamath;

TEST(UnaryArithmeticOperatorParserTests, parseTest) {
  EXPECT_THROW(UnaryArithmeticOperatorParser::parse(""), std::invalid_argument);

  EXPECT_EQ(UnaryArithmeticOperatorParser::parse("10"), nullptr);
  EXPECT_EQ(UnaryArithmeticOperatorParser::parse("(10)"), nullptr);
  EXPECT_EQ(UnaryArithmeticOperatorParser::parse("(-10)"), nullptr);
  EXPECT_EQ(UnaryArithmeticOperatorParser::parse("(+10)"), nullptr);
}