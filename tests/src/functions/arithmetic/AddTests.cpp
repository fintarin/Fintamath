#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AddTests, toStringTest) {
  EXPECT_EQ(Add().toString(), "+");
}

TEST(AddTests, getPriorityTest) {
  EXPECT_EQ(Add().getPriority(), 1);
}

TEST(AddTests, callTest) {
  EXPECT_EQ(Add()(Integer(3), Integer(5))->toString(), "8");
  EXPECT_EQ(Add()(Integer(3), Rational(5, 2))->toString(), "11/2");
  EXPECT_EQ(Add()(Rational(5, 2), Integer(3))->toString(), "11/2");
  EXPECT_EQ(Add()(Rational(5, 2), Rational(5, 2))->toString(), "5");
  EXPECT_EQ(Add()(Rational(5, 2), Rational(5, 3))->toString(), "25/6");

  EXPECT_ANY_THROW(Add()(Integer(3), Variable("a")));

  std::unique_ptr<Operator> o = std::make_unique<Add>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}

TEST(AddTests, equalsTest) {
  EXPECT_TRUE(Add() == Add());
  EXPECT_FALSE(Add() == Sub());
}
