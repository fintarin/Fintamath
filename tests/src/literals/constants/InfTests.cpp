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

TEST(InfTests, getClassTest) {
  EXPECT_EQ(Inf::getClassStatic(), MathObjectClass("Inf"));
  EXPECT_EQ(Inf::getClassStatic().getParent(), IConstant::getClassStatic());
}
