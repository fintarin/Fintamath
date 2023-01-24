#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"

using namespace fintamath;

const E f;

TEST(ETests, toStringTest) {
  EXPECT_EQ(f.toString(), "E");
}

TEST(ETests, callTest) {
  EXPECT_EQ(f()->toString(), "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
}
