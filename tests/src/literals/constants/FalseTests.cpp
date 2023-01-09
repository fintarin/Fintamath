#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/False.hpp"

using namespace fintamath;

const False f;

TEST(FalseTests, toStringTest) {
  EXPECT_EQ(f.toString(), "false");
}

TEST(FalseTests, callTest) {
  EXPECT_EQ(f()->toString(), "false");
  EXPECT_TRUE(f()->is<Boolean>());
}
