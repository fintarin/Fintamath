#include "gtest/gtest.h"
#include <fintamath/functions/arithmetic/Add.hpp>
#include <fintamath/literals/Variable.hpp>
#include <fintamath/literals/Constant.hpp>

#include <fintamath/functions/trigonometry/Atan.hpp>

using namespace fintamath;

TEST(AtanTests, toStringTest) {
  EXPECT_EQ(Atan().toString(), "atan");
}

TEST(AtanTests, callTest){
  EXPECT_EQ(Atan()(Integer(0))->to<Rational>().toString(5), "0");
  EXPECT_EQ(Atan()(Integer(1))->to<Rational>().toString(36), "0.785398163397448309615660845819875716");
  EXPECT_EQ(Atan()(Integer(10))->to<Rational>().toString(10), "1.4711276743");
  EXPECT_EQ(Atan()(Integer(-10))->to<Rational>().toString(10), "-1.4711276743");
  EXPECT_EQ(Atan()(Rational(1, 10))->to<Rational>().toString(10), "0.0996686525");

  EXPECT_ANY_THROW(Atan()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Atan>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "1.4711276743");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(AtanTests, equalsTest) {
  EXPECT_TRUE(Atan() == Atan());
  EXPECT_FALSE(Atan() == Add());
}
