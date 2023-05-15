#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/False.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const False f;

TEST(FalseTests, toStringTest) {
  EXPECT_EQ(f.toString(), "False");
}

TEST(FalseTests, callTest) {
  EXPECT_EQ(f()->toString(), "False");
  EXPECT_TRUE(is<Boolean>(f()));
}

TEST(FalseTests, equalsTest) {
  False a;

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, False());
  EXPECT_EQ(False(), a);
  EXPECT_NE(a, Pi());
  EXPECT_NE(Pi(), a);
}
