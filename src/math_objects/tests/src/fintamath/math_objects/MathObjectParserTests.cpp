#include <gtest/gtest.h>

#include "fintamath/math_objects/MathObjectParser.hpp"

using namespace fintamath;

TEST(MathObjectParserTests, parseTest) {
  EXPECT_EQ(MathObjectParser::parse("1")->toString(), "1");
  EXPECT_EQ(MathObjectParser::parse("1.1.1"), nullptr);
}
