#include <gtest/gtest.h>

#include "fintamath/functions/constants/Pi.hpp"

using namespace fintamath;

TEST(PiTests, stringConstructorTest) {
  EXPECT_EQ(Pi().toString(), "pi");
}

TEST(PiTests, toStringTest) {
  EXPECT_EQ(Pi().toString(), "pi");
}

TEST(PiTests, callTest) {
  EXPECT_EQ(Pi()().toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
}
