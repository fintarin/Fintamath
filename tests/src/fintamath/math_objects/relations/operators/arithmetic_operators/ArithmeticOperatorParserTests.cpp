#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/ArithmeticOperatorParser.hpp"

using namespace fintamath;

TEST(ArithmeticOperatorParserTests, parseTest) {
  EXPECT_EQ(ArithmeticOperatorParser::parse("10"), nullptr);
  EXPECT_EQ(ArithmeticOperatorParser::parse("(10)"), nullptr);

  EXPECT_THROW(ArithmeticOperatorParser::parse("+"), std::invalid_argument);
  EXPECT_THROW(ArithmeticOperatorParser::parse("-"), std::invalid_argument);
  EXPECT_THROW(ArithmeticOperatorParser::parse("*"), std::invalid_argument);
  EXPECT_THROW(ArithmeticOperatorParser::parse("/"), std::invalid_argument);
}
