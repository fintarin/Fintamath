#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/literals/Constant.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(CosTests, toStringTest) {
  EXPECT_EQ(Cos().toString(), "cos");
}

TEST(CosTests, callTest) {
  EXPECT_EQ(Cos()(Integer(0))->to<Rational>().toString(5), "1");
  EXPECT_EQ(Cos()(Integer(10))->to<Rational>().toString(10), "-0.8390715291");
  EXPECT_EQ(Cos()(Integer(5))->to<Rational>().toString(36), "0.283662185463226264466639171513557308");
  EXPECT_EQ(Cos()(Rational(1, 10))->to<Rational>().toString(10), "0.9950041653");
  EXPECT_EQ(Cos()(Constant("pi").toRational(10) / 2)->to<Rational>().toString(5), "-0");

  EXPECT_ANY_THROW(Cos()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Cos>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "-0.8390715291");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(CosTests, equalsTest) {
  EXPECT_TRUE(Cos() == Cos());
  EXPECT_FALSE(Cos() == Add());
}