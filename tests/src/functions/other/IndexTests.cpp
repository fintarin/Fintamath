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
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Exponentiation);
}

TEST(IndexTests, callTest) {
  EXPECT_EQ(f(Variable("a"), Integer(1))->toString(), "a_1");
  EXPECT_EQ(f(Variable("a"), Integer(2))->toString(), "a_2");
  EXPECT_EQ(f(Variable("a"), Integer("100000000000000000000000000000000"))->toString(),
            "a_100000000000000000000000000000000");

  EXPECT_THROW(f(Variable("a"), Variable("a"))->toString(), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Expression("a+1"))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("x"), Integer(0))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("x"), Integer(-1))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("1"), Integer(2))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("a+1"), Integer(2))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("a+1"), Expression("a+1"))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("a"), Expression("a>1"))->toString(), InvalidInputException);
}
