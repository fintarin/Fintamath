#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"


using namespace fintamath;

TEST(ETests, constructorTest) {
  EXPECT_EQ(E().toString(), "e");
}

TEST(ETests, toRationalTest) {
  EXPECT_EQ(E().getValue(1).toString(72),
            "2.71828182845904523536028747135266249775724709369995957496696762772407663");
  EXPECT_EQ(E().getValue(100).toString(100),
            "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274");
}

TEST(ETests, toStringTest) {
  EXPECT_EQ(E().toString(), "e");
}

