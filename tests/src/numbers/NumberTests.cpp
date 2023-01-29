#include <gtest/gtest.h>

#include "fintamath/numbers/INumber.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(NumberTests, addTest) {
  NumberPtr m1 = std::make_unique<Integer>(1);
  NumberPtr m2 = std::make_unique<Rational>(2);
  NumberPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 + *m1)->toString(), "2");
  EXPECT_EQ((*m2 + *m2)->toString(), "4");
  EXPECT_EQ((*m1 + *m2)->toString(), "3");
  EXPECT_EQ((*m2 + *m1)->toString(), "3");

  EXPECT_EQ((*m1 + *m3)->toString(), "3/2");
  EXPECT_EQ((*m2 + *m3)->toString(), "5/2");
  EXPECT_EQ((*m3 + *m1)->toString(), "3/2");
  EXPECT_EQ((*m3 + *m2)->toString(), "5/2");
}

TEST(NumberTests, subTest) {
  NumberPtr m1 = std::make_unique<Integer>(1);
  NumberPtr m2 = std::make_unique<Rational>(2);
  NumberPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 - *m1)->toString(), "0");
  EXPECT_EQ((*m2 - *m2)->toString(), "0");
  EXPECT_EQ((*m1 - *m2)->toString(), "-1");
  EXPECT_EQ((*m2 - *m1)->toString(), "1");

  EXPECT_EQ((*m1 - *m3)->toString(), "1/2");
  EXPECT_EQ((*m2 - *m3)->toString(), "3/2");
  EXPECT_EQ((*m3 - *m1)->toString(), "-1/2");
  EXPECT_EQ((*m3 - *m2)->toString(), "-3/2");
}

TEST(NumberTests, mulTest) {
  NumberPtr m1 = std::make_unique<Integer>(1);
  NumberPtr m2 = std::make_unique<Rational>(2);
  NumberPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 * *m1)->toString(), "1");
  EXPECT_EQ((*m2 * *m2)->toString(), "4");
  EXPECT_EQ((*m1 * *m2)->toString(), "2");
  EXPECT_EQ((*m2 * *m1)->toString(), "2");

  EXPECT_EQ((*m1 * *m3)->toString(), "1/2");
  EXPECT_EQ((*m2 * *m3)->toString(), "1");
  EXPECT_EQ((*m3 * *m1)->toString(), "1/2");
  EXPECT_EQ((*m3 * *m2)->toString(), "1");
}

TEST(NumberTests, divTest) {
  NumberPtr m1 = std::make_unique<Integer>(1);
  NumberPtr m2 = std::make_unique<Integer>(5);
  NumberPtr m3 = std::make_unique<Rational>(2);
  NumberPtr m4 = std::make_unique<Rational>(1, 2);

  EXPECT_EQ((*m1 / *m2)->toString(), "1/5");

  EXPECT_EQ((*m1 / *m1)->toString(), "1");
  EXPECT_EQ((*m3 / *m3)->toString(), "1");
  EXPECT_EQ((*m1 / *m3)->toString(), "1/2");
  EXPECT_EQ((*m3 / *m1)->toString(), "2");

  EXPECT_EQ((*m1 / *m4)->toString(), "2");
  EXPECT_EQ((*m3 / *m4)->toString(), "4");
  EXPECT_EQ((*m4 / *m1)->toString(), "1/2");
  EXPECT_EQ((*m4 / *m3)->toString(), "1/4");
}
