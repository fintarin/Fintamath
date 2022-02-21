#include <gtest/gtest.h>

#include "fintamath/math_objects/nodes/terms/TermParser.hpp"

using namespace fintamath;

TEST(TermParserTests, parseTest) {
  EXPECT_EQ(TermParser::parse("1")->toString(), "1");
  EXPECT_EQ(TermParser::parse("2.2.2"), nullptr);
}
