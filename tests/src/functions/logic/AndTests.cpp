#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/And.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

using F = And;
const F f;

TEST(AndTests, toStringTest) {
  EXPECT_EQ(f.toString(), "&");
}

TEST(AndTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(Boolean::getTypeStatic(), Boolean::getTypeStatic()));
}

TEST(AndTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), Boolean::getTypeStatic());
}

TEST(AndTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AndTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AndTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::Conjunction);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Conjunction);
}

TEST(AndTests, isAssociativeTest) {
  EXPECT_TRUE(F::isAssociativeStatic());
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

TEST(AndTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::And);
  EXPECT_EQ(f.getType(), MathObjectType::And);
}
