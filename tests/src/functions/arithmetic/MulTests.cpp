#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(MulTests, toStringTest) {
  EXPECT_EQ(Mul().toString(), "*");
}

TEST(MulTests, getPriorityTest) {
  EXPECT_EQ(Mul().getPriority(), 2);
}

TEST(MulTests, callTest) {
  EXPECT_EQ(Mul()(Integer(3), Integer(5))->toString(), "15");
  EXPECT_EQ(Mul()(Integer(3), Rational(5, 2))->toString(), "15/2");
  EXPECT_EQ(Mul()(Rational(5, 2), Integer(3))->toString(), "15/2");
  EXPECT_EQ(Mul()(Rational(5, 2), Rational(5, 3))->toString(), "25/6");

  EXPECT_ANY_THROW(Mul()(Integer(3), Variable("a")));

  std::unique_ptr<Operator> o = std::make_unique<Mul>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}

TEST(MulTests, equalsTest) {
  EXPECT_TRUE(Mul() == Mul());
  EXPECT_FALSE(Mul() == Sub());
}