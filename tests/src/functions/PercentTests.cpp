#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/variables/Variable.hpp>
#include <fintamath/constants/Constant.hpp>

#include <fintamath/functions/Percent.hpp>

using namespace fintamath;

TEST(PercentTests, toStringTest) {
  EXPECT_EQ(Percent().toString(), "%");
}

TEST(PercentTests, callTest){
  EXPECT_EQ(Percent()(Integer(1))->to<Rational>().toString(5), "0.01");
  EXPECT_EQ(Percent()(Integer(1000))->to<Rational>().toString(10), "10");
  EXPECT_EQ(Percent()(Integer(-10))->to<Rational>().toString(10), "-0.1");
  EXPECT_EQ(Percent()(Rational(1, 10))->to<Rational>().toString(10), "0.001");

  EXPECT_ANY_THROW(Percent()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Percent>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "0.1");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(PercentTests, equalsTest) {
  EXPECT_TRUE(Percent() == Percent());
  EXPECT_FALSE(Percent() == Add());
}