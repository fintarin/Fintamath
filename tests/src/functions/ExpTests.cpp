#include "gtest/gtest.h"
#include <fintamath/operators/Neg.hpp>
#include <fintamath/variables/Variable.hpp>

#include "fintamath/functions/Exp.hpp"

using namespace fintamath;

TEST(ExpTests, toStringTest) {
  EXPECT_EQ(Exp().toString(), "exp");
}

TEST(ExpTests, callTest){
  EXPECT_EQ(Exp()(Integer(3))->to<Rational>().toString(10), "20.0855369232");
  EXPECT_EQ(Exp()(Integer(3))->to<Rational>().toString(36), "20.085536923187667740928529654581717897");
  EXPECT_EQ(Exp()(Integer(-3))->to<Rational>().toString(10), "0.0497870684");
  EXPECT_EQ(Exp()(Rational(1, 3))->to<Rational>().toString(10), "1.3956124251");

  EXPECT_ANY_THROW(Exp()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Exp>();
  EXPECT_EQ((*f)(Integer(3))->to<Rational>().toString(10), "20.0855369232");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1)));
}

TEST(ExpTests, equalsTest) {
  EXPECT_TRUE(Exp() == Exp());
  EXPECT_FALSE(Exp() == Neg());
}