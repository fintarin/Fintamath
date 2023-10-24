#include <gtest/gtest.h>

#include "fintamath/numbers/RationalFunctions.hpp"

using namespace fintamath;

TEST(RationalFunctionsTests, floorTest) {
  EXPECT_EQ(floor(Rational("-1000.8")).toString(), "-1001");
  EXPECT_EQ(floor(Rational("-1000.1")).toString(), "-1001");
  EXPECT_EQ(floor(Rational("-1000")).toString(), "-1000");
  EXPECT_EQ(floor(Rational("-1.9")).toString(), "-2");
  EXPECT_EQ(floor(Rational("-1.5")).toString(), "-2");
  EXPECT_EQ(floor(Rational("-1.3")).toString(), "-2");
  EXPECT_EQ(floor(Rational("-1")).toString(), "-1");
  EXPECT_EQ(floor(Rational("-0.9")).toString(), "-1");
  EXPECT_EQ(floor(Rational("-0.3")).toString(), "-1");
  EXPECT_EQ(floor(Rational("0")).toString(), "0");
  EXPECT_EQ(floor(Rational("0.3")).toString(), "0");
  EXPECT_EQ(floor(Rational("0.9")).toString(), "0");
  EXPECT_EQ(floor(Rational("1")).toString(), "1");
  EXPECT_EQ(floor(Rational("1.9")).toString(), "1");
  EXPECT_EQ(floor(Rational("1.5")).toString(), "1");
  EXPECT_EQ(floor(Rational("1.3")).toString(), "1");
  EXPECT_EQ(floor(Rational("1000")).toString(), "1000");
  EXPECT_EQ(floor(Rational("1000.1")).toString(), "1000");
  EXPECT_EQ(floor(Rational("1000.8")).toString(), "1000");
}

TEST(RationalFunctionsTests, ceilTest) {
  EXPECT_EQ(ceil(Rational("-1000.8")).toString(), "-1000");
  EXPECT_EQ(ceil(Rational("-1000.1")).toString(), "-1000");
  EXPECT_EQ(ceil(Rational("-1000")).toString(), "-1000");
  EXPECT_EQ(ceil(Rational("-1.9")).toString(), "-1");
  EXPECT_EQ(ceil(Rational("-1.5")).toString(), "-1");
  EXPECT_EQ(ceil(Rational("-1.3")).toString(), "-1");
  EXPECT_EQ(ceil(Rational("-1")).toString(), "-1");
  EXPECT_EQ(ceil(Rational("-0.9")).toString(), "0");
  EXPECT_EQ(ceil(Rational("-0.3")).toString(), "0");
  EXPECT_EQ(ceil(Rational("0")).toString(), "0");
  EXPECT_EQ(ceil(Rational("0.3")).toString(), "1");
  EXPECT_EQ(ceil(Rational("0.9")).toString(), "1");
  EXPECT_EQ(ceil(Rational("1")).toString(), "1");
  EXPECT_EQ(ceil(Rational("1.9")).toString(), "2");
  EXPECT_EQ(ceil(Rational("1.5")).toString(), "2");
  EXPECT_EQ(ceil(Rational("1.3")).toString(), "2");
  EXPECT_EQ(ceil(Rational("1000")).toString(), "1000");
  EXPECT_EQ(ceil(Rational("1000.1")).toString(), "1001");
  EXPECT_EQ(ceil(Rational("1000.8")).toString(), "1001");
}

TEST(RationalFunctionsTests, absTest) {
  EXPECT_EQ(abs(Rational(-1, 100)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(1, -100)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(10, 1000)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(0)).toString(), "0");
}
