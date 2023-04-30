#include <gtest/gtest.h>

#include "fintamath/numbers/RationalFunctions.hpp"

#include "fintamath/numbers/NumberFunctions.hpp"

using namespace fintamath;

TEST(RationalFunctionsTests, absTest) {
  EXPECT_EQ(abs(Rational(-1, 100)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(1, -100)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(10, 1000)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(0)).toString(), "0");
}
