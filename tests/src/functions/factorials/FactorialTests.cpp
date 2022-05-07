#include "gtest/gtest.h"

#include "fintamath/functions/factorials/Factorial.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(FactorialTests, toStringTest) {
  EXPECT_EQ(Factorial().toString(), "!");
}

TEST(FactorialTests, callTest) {
  EXPECT_EQ(Factorial()(Integer(0))->toString(), "1");
  EXPECT_EQ(Factorial()(Integer(1))->toString(), "1");
  EXPECT_EQ(Factorial()(Integer(10))->toString(), "3628800");

  EXPECT_ANY_THROW(Factorial()(Variable("a")));
  EXPECT_ANY_THROW(Factorial()(Integer(-10)));
  EXPECT_ANY_THROW(Factorial()(Rational(1, 10)));

  std::unique_ptr<Function> f = std::make_unique<Factorial>();
  EXPECT_EQ((*f)(Integer(5))->toString(), "120");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
