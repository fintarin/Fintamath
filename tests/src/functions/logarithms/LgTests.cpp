#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/literals/Variable.hpp>

#include <fintamath/functions/logarithms/Lg.hpp>

using namespace fintamath;

TEST(LgTests, toStringTest) {
  EXPECT_EQ(Lg().toString(), "lg");
}

TEST(LgTests, callTest){
  EXPECT_EQ(Lg()(Integer(10))->to<Rational>().toString(10), "1");
  EXPECT_EQ(Lg()(Integer(20))->to<Rational>().toString(10), "1.3010299957");
  EXPECT_EQ(Lg()(Integer(2))->to<Rational>().toString(36), "0.301029995663981195213738894724493001");
  EXPECT_EQ(Lg()(Rational(1, 10))->to<Rational>().toString(10), "-1");

  EXPECT_ANY_THROW(Lg()(Variable("a")));
  EXPECT_ANY_THROW(Lg()(Integer(-10)));

  std::unique_ptr<Function> f = std::make_unique<Lg>();
  EXPECT_EQ((*f)(Integer(20))->to<Rational>().toString(10), "1.3010299957");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(10), Integer(10), Integer(10)));
}

TEST(LgTests, equalsTest) {
  EXPECT_TRUE(Lg() == Lg());
  EXPECT_FALSE(Lg() == Add());
}