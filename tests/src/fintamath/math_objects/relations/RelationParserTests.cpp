#include <gtest/gtest.h>

#include "fintamath/math_objects/relations/RelationParser.hpp"

using namespace fintamath;

TEST(RelationParserTests, parseTest) {
  EXPECT_EQ(RelationParser::parse("10"), nullptr);
}
