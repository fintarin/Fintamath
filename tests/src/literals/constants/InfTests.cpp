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

TEST(InfTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, Inf());
  EXPECT_EQ(Inf(), c);
  EXPECT_EQ(c, cast<IMathObject>(Inf()));
  EXPECT_EQ(cast<IMathObject>(Inf()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}

TEST(InfTests, getTypeTest) {
  EXPECT_EQ(Inf::getTypeStatic(), MathObjectType::Inf);
  EXPECT_EQ(Inf().getType(), MathObjectType::Inf);
}
