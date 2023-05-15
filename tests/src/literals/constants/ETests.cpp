#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const E f;

TEST(ETests, toStringTest) {
  EXPECT_EQ(f.toString(), "E");
}

TEST(ETests, callTest) {
  EXPECT_EQ(f()->toString(), "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
}

TEST(ETests, equalsTest) {
  E a;

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, E());
  EXPECT_EQ(E(), a);
  EXPECT_NE(a, Pi());
  EXPECT_NE(Pi(), a);
}
