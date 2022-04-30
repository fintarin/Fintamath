#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/variables/Variable.hpp>
#include <fintamath/constants/Constant.hpp>

#include <fintamath/functions/DoubleFactorial.hpp>

using namespace fintamath;

TEST(DoubleFactorialTests, toStringTest) {
  EXPECT_EQ(DoubleFactorial().toString(), "!!");
}

TEST(DoubleFactorialTests, callTest){
  EXPECT_EQ(DoubleFactorial()(Integer(0))->to<Rational>().toString(), "1");
  EXPECT_EQ(DoubleFactorial()(Integer(1))->to<Rational>().toString(), "1");
  EXPECT_EQ(DoubleFactorial()(Integer(5))->to<Rational>().toString(), "15");
  EXPECT_EQ(DoubleFactorial()(Integer(10))->to<Rational>().toString(), "3840");

  EXPECT_ANY_THROW(DoubleFactorial()(Variable("a")));
  EXPECT_ANY_THROW(DoubleFactorial()(Integer(-10)));
  EXPECT_ANY_THROW(DoubleFactorial()(Rational(1, 10)));

  std::unique_ptr<Function> f = std::make_unique<DoubleFactorial>();
  EXPECT_EQ((*f)(Integer(10))->to<Rational>().toString(), "3840");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(DoubleFactorialTests, equalsTest) {
  EXPECT_TRUE(DoubleFactorial() == DoubleFactorial());
  EXPECT_FALSE(DoubleFactorial() == Add());
}