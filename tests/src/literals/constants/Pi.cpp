#include <gtest/gtest.h>

#include "fintamath/literals/constants/Pi.hpp"


using namespace fintamath;

TEST(PiTests, stringConstructorTest) {
  EXPECT_EQ(Pi().toString(), "pi");
}

TEST(PiTests, toRationalTest) {
  EXPECT_EQ(Pi().getValue(1).toString(72),
            "3.141592653589793238462643383279502884197169399375105820974944592307816406");
  EXPECT_EQ(Pi().getValue(100).toString(100),
            "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170674");
}

TEST(PiTests, toStringTest) {
  EXPECT_EQ(Pi().toString(), "pi");
}
