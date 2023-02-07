#include "gtest/gtest.h"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/other/Index.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

const Index f;

TEST(IndexTests, toStringTest) {
  EXPECT_EQ(f.toString(), "_");
}

TEST(IndexTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(IndexTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Index);
}

TEST(IndexTests, callTest) {
  EXPECT_EQ(f(Variable("a"), Integer(2))->toString(), "a_2");
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "a_a");
  EXPECT_EQ(f(Expression("a+1"), Integer(2))->toString(), "(a + 1)_2");
  EXPECT_EQ(f(Variable("a"), Expression("a+1"))->toString(), "a_(a + 1)");
  EXPECT_EQ(f(Expression("a+1"), Expression("a+1"))->toString(), "(a + 1)_(a + 1)");
}
