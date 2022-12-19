#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"

using namespace fintamath;

TEST(ETests, constructorTest) {
  EXPECT_EQ(E().toString(), "e");
}

TEST(ETests, toStringTest) {
  EXPECT_EQ(E().toString(), "e");
}

TEST(ETests, callTest) {
  EXPECT_EQ(E()().toString(), "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
}

TEST(ETests, getClassNameTest) {
  EXPECT_EQ(E().getClassName(), "E");
}
