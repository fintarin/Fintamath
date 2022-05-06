#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/literals/Variable.hpp>

#include <fintamath/functions/logarithms/Lb.hpp>

using namespace fintamath;

TEST(LbTests, toStringTest) {
  EXPECT_EQ(Lb().toString(), "lb");
}

TEST(LbTests, callTest){
  EXPECT_EQ(Lb()(Integer(2))->to<Rational>().toString(10), "1");
  EXPECT_EQ(Lb()(Integer(10))->to<Rational>().toString(10), "3.3219280949");
  EXPECT_EQ(Lb()(Integer(3))->to<Rational>().toString(36), "1.584962500721156181453738943947816535");
  EXPECT_EQ(Lb()(Rational(1, 16))->to<Rational>().toString(10), "-4");

  EXPECT_ANY_THROW(Lb()(Variable("a")));
  EXPECT_ANY_THROW(Lb()(Integer(-10)));

  std::unique_ptr<Function> f = std::make_unique<Lb>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "3.3219280949");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(10), Integer(10), Integer(10)));
}

TEST(LbTests, equalsTest) {
  EXPECT_TRUE(Lb() == Lb());
  EXPECT_FALSE(Lb() == Add());
}