#include "gtest/gtest.h"

#include "fintamath/functions/logic/Or.hpp"

#include "fintamath/literals/Boolean.hpp"

using namespace fintamath;

TEST(OrTests, toStringTest) {
  EXPECT_EQ(Or().toString(), "||");
}

TEST(OrTests, getFunctionTypeTest) {
  EXPECT_EQ(Or().getFunctionType(), IFunction::Type::Binary);
}

TEST(OrTests, getOperatorPriorityTest) {
  EXPECT_EQ(Or().getOperatorPriority(), IOperator::Priority::Or);
}

TEST(OrTests, callTest) {
  EXPECT_EQ(Or()(Boolean(false), Boolean(false))->toString(), "false");
  EXPECT_EQ(Or()(Boolean(false), Boolean(true))->toString(), "true");
  EXPECT_EQ(Or()(Boolean(true), Boolean(false))->toString(), "true");
  EXPECT_EQ(Or()(Boolean(true), Boolean(true))->toString(), "true");
}
