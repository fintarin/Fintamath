#include "gtest/gtest.h"

#include "fintamath/functions/comparison/Eqv.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(EqTests, toStringTest) {
  EXPECT_EQ(Eqv().toString(), "=");
}

TEST(EqTests, getFunctionTypeTest) {
  EXPECT_EQ(Eqv().getFunctionType(), IFunction::Type::Binary);
}

TEST(EqTests, getOperatorPriorityTest) {
  EXPECT_EQ(Eqv().getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(EqTests, callTest) {
  EXPECT_EQ(Eqv()(Integer(5), Integer(3))->toString(), "false");
  EXPECT_EQ(Eqv()(Integer(3), Integer(5))->toString(), "false");
  EXPECT_EQ(Eqv()(Integer(3), Integer(3))->toString(), "true");
  EXPECT_EQ(Eqv()(Integer(3), Rational(3, 1))->toString(), "true");
  EXPECT_EQ(Eqv()(Rational(5, 2), Integer(2))->toString(), "false");
  EXPECT_EQ(Eqv()(Integer(3), Variable("a"))->toString(), "false");
  EXPECT_EQ(Eqv()(Variable("a"), Variable("a"))->toString(), "true");

  std::unique_ptr<IOperator> o = std::make_unique<Eqv>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
