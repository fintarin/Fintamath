#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/literals/Variable.hpp>
#include <fintamath/literals/Constant.hpp>

#include <fintamath/functions/Cot.hpp>

using namespace fintamath;

TEST(CotTests, toStringTest) {
  EXPECT_EQ(Cot().toString(), "cot");
}

TEST(CotTests, callTest){
  EXPECT_EQ(Cot()(Constant("pi").toRational(10) / 2)->to<Rational>().toString(5), "-0");
  EXPECT_EQ(Cot()(Integer(10))->to<Rational>().toString(10), "1.5423510454");
  EXPECT_EQ(Cot()(Integer(-10))->to<Rational>().toString(10), "-1.5423510454");
  EXPECT_EQ(Cot()(Integer(5))->to<Rational>().toString(36), "-0.295812915532745540427767168082485287");
  EXPECT_EQ(Cot()(Rational(1, 10))->to<Rational>().toString(10), "9.9666444233");
  EXPECT_EQ(Cot()(Constant("pi").toRational(10) / 4)->to<Rational>().toString(5), "1");

  EXPECT_ANY_THROW(Cot()(Variable("a")));
  EXPECT_ANY_THROW(Cot()(Integer(0)));

  std::unique_ptr<Function> f = std::make_unique<Cot>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(10), "1.5423510454");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(CotTests, equalsTest) {
  EXPECT_TRUE(Cot() == Cot());
  EXPECT_FALSE(Cot() == Add());
}