#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/True.hpp"

using namespace fintamath;

const True c;

TEST(TrueTests, toStringTest) {
  EXPECT_EQ(c.toString(), "True");
}

TEST(TrueTests, callTest) {
  EXPECT_EQ(c()->toString(), "True");
  EXPECT_TRUE(is<Boolean>(c()));
}

TEST(TrueTests, getTypeTest) {
  EXPECT_EQ(True::getTypeStatic(), MathObjectType(MathObjectType::True, "True"));
  EXPECT_EQ(True().getType(), MathObjectType(MathObjectType::True, "True"));
}
