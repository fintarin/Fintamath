#include "gtest/gtest.h"

#include "fintamath/functions/logic/And.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const And f;

TEST(AndTests, toStringTest) {
  EXPECT_EQ(f.toString(), "&");
}

TEST(AndTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(AndTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Conjunction);
}

TEST(AndTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(AndTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a & b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(AndTests, exprTest) {
  EXPECT_EQ(andExpr(Boolean(true), Boolean(false))->toString(), "True & False");
}

TEST(AndTests, doArgsMatchTest) {
  Boolean a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(AndTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, And());
  EXPECT_EQ(And(), f);
  EXPECT_EQ(f, cast<IMathObject>(And()));
  EXPECT_EQ(cast<IMathObject>(And()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(AndTests, getTypeTest) {
  EXPECT_EQ(And::getTypeStatic(), MathObjectType::And);
  EXPECT_EQ(And().getType(), MathObjectType::And);
}
