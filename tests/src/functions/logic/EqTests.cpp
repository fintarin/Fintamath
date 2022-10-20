#include "gtest/gtest.h"

#include "fintamath/functions/logic/Eq.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(EqTests, toStringTest) {
  EXPECT_EQ(Eq().toString(), "=");
}

TEST(EqTests, getFunctionTypeTest) {
  EXPECT_EQ(Eq().getFunctionType(), IFunction::Type::Binary);
}

TEST(EqTests, getOperatorPriorityTest) {
  EXPECT_EQ(Eq().getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(EqTests, callTest) {
  EXPECT_EQ(Eq()(Integer(5), Integer(3))->toString(), "0");
  EXPECT_EQ(Eq()(Integer(3), Integer(5))->toString(), "0");
  EXPECT_EQ(Eq()(Integer(3), Integer(3))->toString(), "1");
  EXPECT_EQ(Eq()(Integer(3), Rational(3, 1))->toString(), "1");
  EXPECT_EQ(Eq()(Rational(5, 2), Integer(2))->toString(), "0");
  EXPECT_EQ(Eq()(Integer(3), Variable("a"))->toString(), "0");
  EXPECT_EQ(Eq()(Variable("a"), Variable("a"))->toString(), "1");

  std::unique_ptr<IOperator> o = std::make_unique<Eq>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
