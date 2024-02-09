#include "gtest/gtest.h"

#include "fintamath/functions/logic/Equiv.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Equiv f;

TEST(EquivTests, toStringTest) {
  EXPECT_EQ(f.toString(), "<->");
}

TEST(EquivTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(EquivTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Equivalence);
}

TEST(EquivTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(EquivTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "(a & b) | (~a & ~b)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(EquivTests, exprTest) {
  EXPECT_EQ(equivExpr(Boolean(true), Boolean(false))->toString(), "(True & False) | (~True & ~False)");
}

TEST(EquivTests, getTypeTest) {
  EXPECT_EQ(Equiv::getTypeStatic(), MathObjectType::Equiv);
  EXPECT_EQ(Equiv().getType(), MathObjectType::Equiv);
}
