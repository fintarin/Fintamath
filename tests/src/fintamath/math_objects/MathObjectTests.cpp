#include <gtest/gtest.h>

#include "fintamath/math_objects/MathObjectParser.hpp"

using namespace fintamath;

TEST(MathObjectTests, equalityOperatorTest) {
  auto obj1 = MathObjectParser::parse("1");
  auto obj2 = MathObjectParser::parse("1");
  EXPECT_TRUE(*obj1 == *obj2);

  obj2 = MathObjectParser::parse("2");
  EXPECT_FALSE(*obj1 == *obj2);
}

TEST(MathObjectTests, nonequalityOperatorTest) {
  auto obj1 = MathObjectParser::parse("1");
  auto obj2 = MathObjectParser::parse("1");
  EXPECT_FALSE(*obj1 != *obj2);

  obj2 = MathObjectParser::parse("2");
  EXPECT_TRUE(*obj1 != *obj2);
}
