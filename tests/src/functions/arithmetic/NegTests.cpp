#include "gtest/gtest.h"
#include <fintamath/functions/arithmetic/Sub.hpp>
#include <fintamath/literals/Variable.hpp>

#include "fintamath/functions/arithmetic/Neg.hpp"

using namespace fintamath;

TEST(NegTests, toStringTest) {
  EXPECT_EQ(Neg().toString(), "-");
}

TEST(NegTests, getPriorityTest) {
  EXPECT_EQ(Neg().getPriority(), 1);
}

TEST(NegTests, callTest){
  EXPECT_EQ(Neg()(Integer(3))->toString(), "-3");
  EXPECT_EQ(Neg()(Rational(5, 2))->toString(), "-5/2");

  EXPECT_ANY_THROW(Neg()(Variable("a")));

  std::unique_ptr<Operator> o = std::make_unique<Neg>();
  EXPECT_ANY_THROW((*o)(Integer(1), Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}

TEST(NegTests, equalsTest) {
  EXPECT_TRUE(Neg() == Neg());
  EXPECT_FALSE(Neg() == Sub());
}