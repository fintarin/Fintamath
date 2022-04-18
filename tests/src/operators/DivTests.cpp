#include "gtest/gtest.h"
#include <fintamath/operators/Sub.hpp>
#include <fintamath/variables/Variable.hpp>

#include "fintamath/operators/Div.hpp"

using namespace fintamath;

TEST(DivTests, toStringTest) {
  EXPECT_EQ(Div().toString(), "/");
}

TEST(DivTests, getPriorityTest) {
  EXPECT_EQ(Div().getPriority(), 2);
}

TEST(DivTests, callTest){
  EXPECT_EQ(Div()(Integer(3), Integer(5))->toString(), "3/5");
  EXPECT_EQ(Div()(Integer(3), Rational(5, 2))->toString(), "6/5");
  EXPECT_EQ(Div()(Rational(5, 2), Integer(3))->toString(), "5/6");
  EXPECT_EQ(Div()(Rational(5, 2), Rational(5, 3))->toString(), "3/2");

  EXPECT_ANY_THROW(Div()(Integer(3), Variable("a")));

  std::unique_ptr<Operator> o = std::make_unique<Div>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}

TEST(DivTests, equalsTest) {
  EXPECT_TRUE(Div() == Div());
  EXPECT_FALSE(Div() == Sub());
}