#include <gtest/gtest.h>

#include "fintamath/functions/Function.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(FunctionTests, callTests) {
  FunctionPtr f = std::make_unique<Add>();
  Integer a = 3;
  Rational b(1, 2);

  EXPECT_EQ((*f)(a, a)->toString(), "6");
  EXPECT_EQ((*f)(b, b)->toString(), "1");
  EXPECT_EQ((*f)(a, b)->toString(), "7/2");
  EXPECT_EQ((*f)(b, a)->toString(), "7/2");

  EXPECT_THROW((*f)(a, Variable("a")), std::invalid_argument);

  EXPECT_THROW((*f)(), std::invalid_argument);
  EXPECT_THROW((*f)(a), std::invalid_argument);
  EXPECT_THROW((*f)(a, a, a), std::invalid_argument);
  EXPECT_THROW((*f)(a, a, a, a, a, a, a), std::invalid_argument);
}

TEST(FunctionTests, equalsTests) {
  EXPECT_TRUE(Add() == Add());

  EXPECT_FALSE(Add() == Sub());
  EXPECT_FALSE(Sub() == Add());
}
