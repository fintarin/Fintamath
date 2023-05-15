#include <gtest/gtest.h>

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/True.hpp"

using namespace fintamath;

const True f;

TEST(TrueTests, toStringTest) {
  EXPECT_EQ(f.toString(), "True");
}

TEST(TrueTests, callTest) {
  EXPECT_EQ(f()->toString(), "True");
  EXPECT_TRUE(is<Boolean>(f()));
}

TEST(TrueTests, equalsTest) {
  True a;

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, True());
  EXPECT_EQ(True(), a);
  EXPECT_NE(a, E());
  EXPECT_NE(E(), a);
}
