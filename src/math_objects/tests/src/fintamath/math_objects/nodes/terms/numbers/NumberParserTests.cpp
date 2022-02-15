#include <gtest/gtest.h>

#include "fintamath/math_objects/nodes/terms/numbers/NumberParser.hpp"

using namespace fintamath;

TEST(NumberParserTests, parseTest) {
  EXPECT_EQ(NumberParser::parse("1")->toString(), "1");
  EXPECT_EQ(NumberParser::parse("2.2")->toString(), "11/5");
  EXPECT_EQ(NumberParser::parse("2.2.2"), nullptr);
}
