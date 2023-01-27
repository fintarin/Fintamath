#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/True.hpp"

using namespace fintamath;

const True f;

TEST(TrueTests, toStringTest) {
  EXPECT_EQ(f.toString(), "True");
}

TEST(TrueTests, callTest) {
  EXPECT_EQ(f()->toString(), "True");
  EXPECT_TRUE(cast<Boolean>(f()));
}
