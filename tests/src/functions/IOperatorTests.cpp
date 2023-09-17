#include <gtest/gtest.h>

#include "fintamath/functions/IOperator.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/powers/Pow.hpp"

using namespace fintamath;

TEST(IOperatorTests, getOperatorPriorityTest) {
  EXPECT_EQ(Add().getOperatorPriority(), IOperator::Priority::Addition);
  EXPECT_EQ(Neg().getOperatorPriority(), IOperator::Priority::PrefixUnary);
  EXPECT_EQ(Factorial().getOperatorPriority(), IOperator::Priority::PostfixUnary);
  EXPECT_EQ(Or().getOperatorPriority(), IOperator::Priority::Disjunction);
}

TEST(IOperatorTests, isAssociativeTest) {
  EXPECT_TRUE(Add().isAssociative());
  EXPECT_FALSE(Neg().isAssociative());
  EXPECT_TRUE(Or().isAssociative());
  EXPECT_FALSE(Pow().isAssociative());
}

TEST(IOperatorTests, getTypeIdTest) {
  EXPECT_EQ(IOperator::getTypeIdStatic(), MathObjectTypeId(MathObjectType::IOperator));
}
