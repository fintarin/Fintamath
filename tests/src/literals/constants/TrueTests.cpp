#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/True.hpp"

using namespace fintamath;

TEST(TrueTests, constructorTest) {
  EXPECT_EQ(True().toString(), "true");
}

TEST(TrueTests, toStringTest) {
  EXPECT_EQ(True().toString(), "true");
}

TEST(TrueTests, callTest) {
  EXPECT_EQ(True()()->toString(), "true");
  EXPECT_TRUE(True()()->is<Boolean>());
}
