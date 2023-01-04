#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/False.hpp"

using namespace fintamath;

TEST(FalseTests, constructorTest) {
  EXPECT_EQ(False().toString(), "false");
}

TEST(FalseTests, toStringTest) {
  EXPECT_EQ(False().toString(), "false");
}

TEST(FalseTests, callTest) {
  EXPECT_EQ(False()()->toString(), "false");
  EXPECT_TRUE(False()()->is<Boolean>());
}
