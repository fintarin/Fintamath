#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(DivTests, toStringTest) {
  EXPECT_EQ(Div().toString(), "/");
}

TEST(DivTests, getFunctionTypeTest) {
  EXPECT_EQ(Div().getFunctionType(), IFunction::Type::Binary);
}

TEST(DivTests, getOperatorPriorityTest) {
  EXPECT_EQ(Div().getOperatorPriority(), IOperator::Priority::Multiplication);
}

TEST(DivTests, callTest) {
  EXPECT_EQ(Div()(Integer(3), Integer(5))->toString(), "3/5");
  EXPECT_EQ(Div()(Integer(3), Rational(5, 2))->toString(), "6/5");
  EXPECT_EQ(Div()(Rational(5, 2), Integer(3))->toString(), "5/6");
  EXPECT_EQ(Div()(Rational(5, 2), Rational(5, 3))->toString(), "3/2");

  EXPECT_EQ(Div()(Integer(3), Variable("a"))->toString(), "3/a");

  std::unique_ptr<IOperator> o = std::make_unique<Div>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}