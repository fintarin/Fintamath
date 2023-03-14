#include <gtest/gtest.h>

#include "fintamath/numbers/INumber.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(NumberTests, addTest) {
   unique_ptr<INumber> m1 = make_unique<Integer>(1);
   unique_ptr<INumber> m2 = make_unique<Rational>(2);
   unique_ptr<INumber> m3 = make_unique<Rational>(1, 2);

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
   unique_ptr<INumber> m1 = make_unique<Integer>(1);
   unique_ptr<INumber> m2 = make_unique<Rational>(2);
   unique_ptr<INumber> m3 = make_unique<Rational>(1, 2);

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
   unique_ptr<INumber> m1 = make_unique<Integer>(1);
   unique_ptr<INumber> m2 = make_unique<Rational>(2);
   unique_ptr<INumber> m3 = make_unique<Rational>(1, 2);

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
   unique_ptr<INumber> m1 = make_unique<Integer>(1);
   unique_ptr<INumber> m2 = make_unique<Integer>(5);
   unique_ptr<INumber> m3 = make_unique<Rational>(2);
   unique_ptr<INumber> m4 = make_unique<Rational>(1, 2);

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

TEST(NumberTests, convertTest) {
   unique_ptr<INumber> m1 = make_unique<Integer>(1);
  EXPECT_EQ((+*m1)->toString(), "1");
  EXPECT_TRUE(is<INumber>(+*m1));
}

TEST(NumberTests, negateTest) {
   unique_ptr<INumber> m1 = make_unique<Integer>(1);
  EXPECT_EQ((-*m1)->toString(), "-1");
  EXPECT_TRUE(is<INumber>(+*m1));
}
