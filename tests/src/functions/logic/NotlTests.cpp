#include "gtest/gtest.h"

#include "fintamath/functions/logic/Not.hpp"

using namespace fintamath;

TEST(NotTests, toStringTest) {
  EXPECT_EQ(Not().toString(), "!");
}

TEST(NotTests, getFunctionTypeTest) {
  EXPECT_EQ(Not().getFunctionType(), IFunction::Type::Unary);
}

TEST(NotTests, getOperatorPriorityTest) {
  EXPECT_EQ(Not().getOperatorPriority(), IOperator::Priority::PrefixUnary);
}

TEST(NotTests, callTest) {
  EXPECT_EQ(Not()(Boolean(true))->toString(), "false");
  EXPECT_EQ(Not()(Boolean(false))->toString(), "true");
}
