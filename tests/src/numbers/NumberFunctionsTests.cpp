#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(NumberFunctionsTests, addTest) {
  const INumber &integer = Integer(2);
  const INumber &rational = Rational(3, 4);
  const INumber &real = Real(1) / 3;

  EXPECT_EQ((integer + integer)->toString(), "4");

  EXPECT_EQ((rational + rational)->toString(), "3/2");
  EXPECT_EQ((rational + integer)->toString(), "11/4");
  EXPECT_EQ((integer + rational)->toString(), "11/4");

  EXPECT_EQ((real + real)->toString(), "0.66666666666666666667");
  EXPECT_EQ((real + integer)->toString(), "2.3333333333333333333");
  EXPECT_EQ((integer + real)->toString(), "2.3333333333333333333");
  EXPECT_EQ((real + rational)->toString(), "1.0833333333333333333");
  EXPECT_EQ((rational + real)->toString(), "1.0833333333333333333");
}
