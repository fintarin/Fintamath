#include "gtest/gtest.h"

#include "fintamath/functions/logic/Not.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Not f;

TEST(NotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "~");
}

TEST(NotTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(NotTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PrefixUnary);
}

TEST(NotTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(NotTests, callTest) {
  EXPECT_EQ(f(Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(false))->toString(), "True");

  EXPECT_EQ(f(Variable("a"))->toString(), "~a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(NotTests, exprTest) {
  EXPECT_EQ(notExpr(Boolean(true))->toString(), "~True");
}

TEST(NotTests, doArgsMatchTest) {
  Boolean a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(NotTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Not());
  EXPECT_EQ(Not(), f);
  EXPECT_EQ(f, cast<IMathObject>(Not()));
  EXPECT_EQ(cast<IMathObject>(Not()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(NotTests, getTypeTest) {
  EXPECT_EQ(Not::getTypeStatic(), MathObjectType::Not);
  EXPECT_EQ(Not().getType(), MathObjectType::Not);
}
