#include "gtest/gtest.h"

#include "fintamath/functions/logic/Not.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Not f;

TEST(NotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "!");
}

TEST(NotTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(NotTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PrefixUnary);
}

TEST(NotTests, callTest) {
  EXPECT_EQ(f(Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(false))->toString(), "True");

  EXPECT_EQ(f(Variable("a"))->toString(), "!a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}
