#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(NumberFunctionsTests, addTest) {
  EXPECT_EQ((makeShared<Integer>(2) + makeShared<Integer>(2))->toString(), "4");

  EXPECT_EQ((makeShared<Rational>(3, 4) + makeShared<Rational>(3, 4))->toString(), "3/2");
  EXPECT_EQ((makeShared<Rational>(1, 2) + makeShared<Rational>(2, 4))->toString(), "1");
  EXPECT_EQ((makeShared<Rational>(3, 4) + makeShared<Integer>(2))->toString(), "11/4");
  EXPECT_EQ((makeShared<Integer>(2) + makeShared<Rational>(3, 4))->toString(), "11/4");

  EXPECT_EQ((makeShared<Real>(Rational(1, 3)) + makeShared<Real>(Rational(1, 3)))->toString(), "0.66666666666666666667");
  EXPECT_EQ((makeShared<Real>(Rational(1, 3)) + makeShared<Integer>(2))->toString(), "2.3333333333333333333");
  EXPECT_EQ((makeShared<Integer>(2) + makeShared<Real>(Rational(1, 3)))->toString(), "2.3333333333333333333");
  EXPECT_EQ((makeShared<Real>(Rational(1, 3)) + makeShared<Rational>(3, 4))->toString(), "1.0833333333333333333");
  EXPECT_EQ((makeShared<Rational>(3, 4) + makeShared<Real>(Rational(1, 3)))->toString(), "1.0833333333333333333");
}
