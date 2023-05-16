#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/False.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const False c;

TEST(FalseTests, toStringTest) {
  EXPECT_EQ(c.toString(), "False");
}

TEST(FalseTests, callTest) {
  EXPECT_EQ(c()->toString(), "False");
  EXPECT_TRUE(is<Boolean>(c()));
}

TEST(FalseTests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, False());
  EXPECT_EQ(False(), c);
  EXPECT_EQ(c, cast<IMathObject>(False()));
  EXPECT_EQ(cast<IMathObject>(False()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}
