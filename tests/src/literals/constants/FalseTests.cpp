#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/False.hpp"

using namespace fintamath;

const False f;

TEST(FalseTests, toStringTest) {
  EXPECT_EQ(f.toString(), "False");
}

TEST(FalseTests, callTest) {
  EXPECT_EQ(f()->toString(), "False");
  EXPECT_TRUE(is<Boolean>(f()));
}
