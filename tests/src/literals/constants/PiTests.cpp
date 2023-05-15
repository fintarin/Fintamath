#include <gtest/gtest.h>

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const Pi f;

TEST(PiTests, toStringTest) {
  EXPECT_EQ(f.toString(), "Pi");
}

TEST(PiTests, callTest) {
  EXPECT_EQ(f()->toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
}

TEST(PiTests, equalsTest) {
  Pi a;

  EXPECT_EQ(a, a);
  EXPECT_EQ(a, Pi());
  EXPECT_EQ(Pi(), a);
  EXPECT_NE(a, E());
  EXPECT_NE(E(), a);
}
