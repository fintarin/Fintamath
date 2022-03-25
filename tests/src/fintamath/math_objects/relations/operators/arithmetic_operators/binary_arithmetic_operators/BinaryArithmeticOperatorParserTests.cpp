#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperatorParser.hpp"

using namespace fintamath;

TEST(BinaryArithmeticOperatorParserTests, parseTest) {
  EXPECT_EQ(BinaryArithmeticOperatorParser::parse("10"), nullptr);
  EXPECT_EQ(BinaryArithmeticOperatorParser::parse("+10"), nullptr);
  EXPECT_EQ(BinaryArithmeticOperatorParser::parse("-10"), nullptr);

  EXPECT_THROW(BinaryArithmeticOperatorParser::parse("10+"), std::invalid_argument);
  EXPECT_THROW(BinaryArithmeticOperatorParser::parse("10-"), std::invalid_argument);
  EXPECT_THROW(BinaryArithmeticOperatorParser::parse("*10"), std::invalid_argument);
  EXPECT_THROW(BinaryArithmeticOperatorParser::parse("/10"), std::invalid_argument);
  EXPECT_THROW(BinaryArithmeticOperatorParser::parse("10*"), std::invalid_argument);
  EXPECT_THROW(BinaryArithmeticOperatorParser::parse("10/"), std::invalid_argument);
}