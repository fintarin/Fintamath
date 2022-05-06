#include "gtest/gtest.h"
#include <fintamath/operators/Neg.hpp>
#include <fintamath/literals/Variable.hpp>

#include "fintamath/operators/Sub.hpp"

using namespace fintamath;

TEST(SubTests, toStringTest) {
  EXPECT_EQ(Sub().toString(), "-");
}

TEST(SubTests, getPriorityTest) {
  EXPECT_EQ(Sub().getPriority(), 1);
}

TEST(SubTests, callTest){
  EXPECT_EQ(Sub()(Integer(3), Integer(5))->toString(), "-2");
  EXPECT_EQ(Sub()(Integer(3), Rational(5, 2))->toString(), "1/2");
  EXPECT_EQ(Sub()(Rational(5, 2), Integer(3))->toString(), "-1/2");
  EXPECT_EQ(Sub()(Rational(5, 2), Rational(5, 2))->toString(), "0");
  EXPECT_EQ(Sub()(Rational(5, 2), Rational(5, 3))->toString(), "5/6");

  EXPECT_ANY_THROW(Sub()(Integer(3), Variable("a")));

  std::unique_ptr<Operator> o = std::make_unique<Sub>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}

TEST(SubTests, equalsTest) {
  EXPECT_TRUE(Sub() == Sub());
  EXPECT_FALSE(Sub() == Neg());
}