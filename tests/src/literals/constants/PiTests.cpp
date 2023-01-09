#include <gtest/gtest.h>

#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

const Pi f;

TEST(PiTests, stringConstructorTest) {
  EXPECT_EQ(f.toString(), "pi");
}

TEST(PiTests, toStringTest) {
  EXPECT_EQ(f.toString(), "pi");
}

TEST(PiTests, callTest) {
  EXPECT_EQ(f()->toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
}
