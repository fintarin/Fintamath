#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/literals/Variable.hpp>

#include <fintamath/functions/other/Abs.hpp>

using namespace fintamath;

TEST(AbsTests, toStringTest) {
  EXPECT_EQ(Abs().toString(), "abs");
}

TEST(AbsTests, callTest){
  EXPECT_EQ(Abs()(Integer(10))->toString(), "10");
  EXPECT_EQ(Abs()(Integer(-10))->toString(), "10");
  EXPECT_EQ(Abs()(Rational(-5, 2))->toString(), "5/2");

  EXPECT_ANY_THROW(Abs()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Abs>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "10");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}

TEST(AbsTests, equalsTest) {
  EXPECT_TRUE(Abs() == Abs());
  EXPECT_FALSE(Abs() == Add());
}