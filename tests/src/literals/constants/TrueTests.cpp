#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/True.hpp"

using namespace fintamath;

const True f;

TEST(TrueTests, constructorTest) {
  EXPECT_EQ(f.toString(), "true");
}

TEST(TrueTests, toStringTest) {
  EXPECT_EQ(f.toString(), "true");
}

TEST(TrueTests, callTest) {
  EXPECT_EQ(f()->toString(), "true");
  EXPECT_TRUE(f()->is<Boolean>());
}
