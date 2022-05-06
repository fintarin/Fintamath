#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/literals/Variable.hpp>
#include <fintamath/literals/Constant.hpp>

#include <fintamath/functions/trigonometry/Tan.hpp>

using namespace fintamath;

TEST(TanTests, toStringTest) {
  EXPECT_EQ(Tan().toString(), "tan");
}

TEST(TanTests, callTest){
  EXPECT_EQ(Tan()(Integer(0))->to<Rational>().toString(5), "0");
  EXPECT_EQ(Tan()(Integer(10))->to<Rational>().toString(10), "0.6483608275");
  EXPECT_EQ(Tan()(Integer(-10))->to<Rational>().toString(10), "-0.6483608275");
  EXPECT_EQ(Tan()(Integer(5))->to<Rational>().toString(36), "-3.380515006246585636982705879447343911");
  EXPECT_EQ(Tan()(Rational(1, 10))->to<Rational>().toString(10), "0.1003346721");
  EXPECT_EQ(Tan()(Constant("pi").toRational(10) / 4)->to<Rational>().toString(5), "1");

  EXPECT_ANY_THROW(Tan()(Variable("a")));
  EXPECT_ANY_THROW(Tan()(Constant("pi").toRational(10) / 2));

  std::unique_ptr<Function> f = std::make_unique<Tan>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "0.6483608275");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(TanTests, equalsTest) {
  EXPECT_TRUE(Tan() == Tan());
  EXPECT_FALSE(Tan() == Add());
}