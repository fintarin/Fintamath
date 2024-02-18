#include <gtest/gtest.h>

#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const Inf c;

TEST(InfTests, toStringTest) {
  EXPECT_EQ(c.toString(), "Inf");
}

TEST(InfTests, callTest) {
  EXPECT_EQ(c()->toString(), "Inf");
}

TEST(InfTests, getTypeTest) {
  EXPECT_EQ(Inf::getTypeStatic(), MathObjectType(MathObjectType::Inf, "Inf"));
  EXPECT_EQ(Inf().getType(), MathObjectType(MathObjectType::Inf, "Inf"));
}
