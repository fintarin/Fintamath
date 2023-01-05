#include "gtest/gtest.h"

#include "fintamath/functions/logic/And.hpp"

#include "fintamath/literals/Boolean.hpp"

using namespace fintamath;

TEST(AndTests, toStringTest) {
  EXPECT_EQ(And().toString(), "&&");
}

TEST(AndTests, getFunctionTypeTest) {
  EXPECT_EQ(And().getFunctionType(), IFunction::Type::Binary);
}

TEST(AndTests, getOperatorPriorityTest) {
  EXPECT_EQ(And().getOperatorPriority(), IOperator::Priority::And);
}

TEST(AndTests, callTest) {
  EXPECT_EQ(And()(Boolean(false), Boolean(false))->toString(), "false");
  EXPECT_EQ(And()(Boolean(false), Boolean(true))->toString(), "false");
  EXPECT_EQ(And()(Boolean(true), Boolean(false))->toString(), "false");
  EXPECT_EQ(And()(Boolean(true), Boolean(true))->toString(), "true");
}
