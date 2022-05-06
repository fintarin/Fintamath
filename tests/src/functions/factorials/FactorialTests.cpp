#include "gtest/gtest.h"
#include <fintamath/functions/arithmetic/Add.hpp>
#include <fintamath/literals/Variable.hpp>
#include <fintamath/literals/Constant.hpp>

#include <fintamath/functions/factorials/Factorial.hpp>

using namespace fintamath;

TEST(FactorialTests, toStringTest) {
  EXPECT_EQ(Factorial().toString(), "!");
}

TEST(FactorialTests, callTest){
  EXPECT_EQ(Factorial()(Integer(0))->to<Rational>().toString(), "1");
  EXPECT_EQ(Factorial()(Integer(1))->to<Rational>().toString(), "1");
  EXPECT_EQ(Factorial()(Integer(10))->to<Rational>().toString(), "3628800");

  EXPECT_ANY_THROW(Factorial()(Variable("a")));
  EXPECT_ANY_THROW(Factorial()(Integer(-10)));
  EXPECT_ANY_THROW(Factorial()(Rational(1, 10)));

  std::unique_ptr<Function> f = std::make_unique<Factorial>();
  EXPECT_EQ((*f)(Integer(5))->to<Rational>().toString(), "120");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(FactorialTests, equalsTest) {
  EXPECT_TRUE(Factorial() == Factorial());
  EXPECT_FALSE(Factorial() == Add());
}