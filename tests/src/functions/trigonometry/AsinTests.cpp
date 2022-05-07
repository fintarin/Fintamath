#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Asin.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AsinTests, toStringTest) {
  EXPECT_EQ(Asin().toString(), "asin");
}

TEST(AsinTests, callTest) {
  EXPECT_EQ(Asin()(Integer(0))->to<Rational>().toString(5), "0");
  EXPECT_EQ(Asin()(Integer(1))->to<Rational>().toString(36), "1.570796326794896619231321691639751442");
  EXPECT_EQ(Asin()(Rational(1, 10))->to<Rational>().toString(10), "0.1001674212");
  EXPECT_EQ(Asin()(Rational(-1, 5))->to<Rational>().toString(10), "-0.2013579208");

  EXPECT_ANY_THROW(Asin()(Variable("a")));
  EXPECT_ANY_THROW(Asin()(Integer(10)));

  std::unique_ptr<Function> f = std::make_unique<Asin>();
  EXPECT_EQ((*f)(Rational(1, 10))->to<Rational>().toString(10), "0.1001674212");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(AsinTests, equalsTest) {
  EXPECT_TRUE(Asin() == Asin());
  EXPECT_FALSE(Asin() == Add());
}
