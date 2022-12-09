#include "gtest/gtest.h"

#include "fintamath/functions/comparison/LessEqv.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(LessEqvTests, toStringTest) {
  EXPECT_EQ(LessEqv().toString(), "<=");
}

TEST(LessEqvTests, getFunctionTypeTest) {
  EXPECT_EQ(LessEqv().getFunctionType(), IFunction::Type::Binary);
}

TEST(LessEqvTests, getOperatorPriorityTest) {
  EXPECT_EQ(LessEqv().getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(LessEqvTests, callTest) {
  EXPECT_EQ(LessEqv()(Integer(5), Integer(3))->toString(), "false");
  EXPECT_EQ(LessEqv()(Integer(3), Integer(5))->toString(), "true");
  EXPECT_EQ(LessEqv()(Integer(3), Integer(3))->toString(), "true");
  EXPECT_EQ(LessEqv()(Integer(3), Rational(3, 1))->toString(), "true");
  EXPECT_EQ(LessEqv()(Rational(5, 2), Integer(2))->toString(), "false");

  EXPECT_EQ(LessEqv()(Integer(3), Variable("a"))->toString(), "-a+3<=0");
  EXPECT_EQ(LessEqv()(Variable("a"), Variable("a"))->toString(), "true");

  std::unique_ptr<IOperator> o = std::make_unique<LessEqv>();
  EXPECT_ANY_THROW((*o)(Integer(1)));
  EXPECT_ANY_THROW((*o)(Rational(2, 3)));
  EXPECT_ANY_THROW((*o)());
  EXPECT_ANY_THROW((*o)(Integer(1), Integer(1), Integer(1)));
}
