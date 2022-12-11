#include <gtest/gtest.h>

#include "fintamath/numbers/NumberFunctions.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(NumberFunctionsTests, absTest) {
  EXPECT_EQ(abs(Integer("-210")).toString(), "210");
  EXPECT_EQ(abs(Integer("4545628562")).toString(), "4545628562");

  EXPECT_EQ(abs(Rational(-1, 100)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(1, -100)).toString(), "1/100");
  EXPECT_EQ(abs(Rational(10, 1000)).toString(), "1/100");

  EXPECT_EQ(abs(Real("8465132.321651651")).toString(), "8465132.321651651");
  EXPECT_EQ(abs(Real("-98465136846516354684651.351")).toString(), "98465136846516354684651.351");
}
