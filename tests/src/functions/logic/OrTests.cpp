#include "gtest/gtest.h"

#include "fintamath/functions/logic/Or.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Or f;

TEST(OrTests, toStringTest) {
  EXPECT_EQ(f.toString(), "|");
}

TEST(OrTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(OrTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Disjunction);
}

TEST(OrTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a | b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(OrTests, exprTest) {
  EXPECT_EQ(orExpr(Boolean(true), Boolean(false))->toString(), "True | False");
}

TEST(OrTests, doArgsMatchTest) {
  Boolean a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(OrTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Or());
  EXPECT_EQ(Or(), f);
  EXPECT_EQ(f, cast<IMathObject>(Or()));
  EXPECT_EQ(cast<IMathObject>(Or()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(OrTests, getTypeIdTest) {
  EXPECT_EQ(Or::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Or));
  EXPECT_EQ(Or().getTypeId(), MathObjectTypeId(MathObjectType::Or));
}
