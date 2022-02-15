#include <gtest/gtest.h>

#include "fintamath/math_objects/nodes/NodeParser.hpp"

using namespace fintamath;

TEST(NodeParserTests, parseTest) {
  EXPECT_EQ(NodeParser::parse("1")->toString(), "1");
  EXPECT_EQ(NodeParser::parse("+"), nullptr);
}
