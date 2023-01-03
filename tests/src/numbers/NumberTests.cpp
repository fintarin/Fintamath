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

TEST(NumberTests, diveTest) {
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

TEST(NumberTests, parseTest) {
  EXPECT_EQ(INumber::parse("1231412736218731623872183")->toString(), "1231412736218731623872183");
  EXPECT_TRUE(INumber::parse("1231412736218731623872183")->is<Integer>());

  EXPECT_EQ(INumber::parse("-1231412736218731623872183")->toString(), "-1231412736218731623872183");
  EXPECT_TRUE(INumber::parse("-1231412736218731623872183")->is<Integer>());

  EXPECT_EQ(INumber::parse("0")->toString(), "0");
  EXPECT_TRUE(INumber::parse("0")->is<Integer>());

  EXPECT_EQ(INumber::parse("0.1")->toString(), "1/10");
  EXPECT_TRUE(INumber::parse("0.1")->is<Rational>());

  EXPECT_EQ(INumber::parse(".1")->toString(), "1/10");
  EXPECT_TRUE(INumber::parse(".1")->is<Rational>());

  EXPECT_EQ(INumber::parse("1.")->toString(), "1");
  EXPECT_TRUE(INumber::parse("1.")->is<Rational>());

  EXPECT_EQ(INumber::parse("12323231498721983.12323432432")->toString(), "77020196867012394520214527/6250000000");
  EXPECT_TRUE(INumber::parse("12323231498721983.12323432432")->is<Rational>());

  EXPECT_EQ(INumber::parse("-12323231498721983.12323432432")->toString(), "-77020196867012394520214527/6250000000");
  EXPECT_TRUE(INumber::parse("-12323231498721983.12323432432")->is<Rational>());

  EXPECT_EQ(INumber::parse("--10"), nullptr);
  EXPECT_EQ(INumber::parse("test"), nullptr);
  EXPECT_EQ(INumber::parse(""), nullptr);
  EXPECT_EQ(INumber::parse("+"), nullptr);
  EXPECT_EQ(INumber::parse("939849.0-0023"), nullptr);
  EXPECT_EQ(INumber::parse("a"), nullptr);
  EXPECT_EQ(INumber::parse("a.1"), nullptr);
  EXPECT_EQ(INumber::parse("1.a"), nullptr);
  EXPECT_EQ(INumber::parse("1a.1"), nullptr);
  EXPECT_EQ(INumber::parse("1.1a"), nullptr);
  EXPECT_EQ(INumber::parse("--10.-1"), nullptr);
  EXPECT_EQ(INumber::parse("10.-1"), nullptr);
  EXPECT_EQ(INumber::parse("1-0.1"), nullptr);
  EXPECT_EQ(INumber::parse("10-.1"), nullptr);
  EXPECT_EQ(INumber::parse("10.--1"), nullptr);
}
