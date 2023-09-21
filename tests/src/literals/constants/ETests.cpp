#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const E c;

TEST(ETests, toStringTest) {
  EXPECT_EQ(c.toString(), "E");
}

TEST(ETests, callTest) {
  EXPECT_EQ(c()->toString(), "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
}

TEST(ETests, equalsTest) {
  EXPECT_EQ(c, c);
  EXPECT_EQ(c, E());
  EXPECT_EQ(E(), c);
  EXPECT_EQ(c, cast<IMathObject>(E()));
  EXPECT_EQ(cast<IMathObject>(E()), c);
  EXPECT_NE(c, Pi());
  EXPECT_NE(Pi(), c);
}

TEST(ETests, getTypeTest) {
  EXPECT_EQ(E::getTypeStatic(), MathObjectType::E);
  EXPECT_EQ(E().getType(), MathObjectType::E);
}
