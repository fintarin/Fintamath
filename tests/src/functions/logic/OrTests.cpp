#include "gtest/gtest.h"

#include "fintamath/functions/logic/Or.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Or f;

TEST(OrTests, toStringTest) {
  EXPECT_EQ(f.toString(), "||");
}

TEST(OrTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(OrTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Or);
}

TEST(OrTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "false");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "true");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "true");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "true");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a || b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}
