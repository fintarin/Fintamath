#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Impl.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

using F = Impl;
const F f;

TEST(ImplTests, toStringTest) {
  EXPECT_EQ(f.toString(), "->");
}

TEST(ImplTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(Boolean::getTypeStatic(), Boolean::getTypeStatic()));
}

TEST(ImplTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), Boolean::getTypeStatic());
}

TEST(ImplTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(ImplTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(ImplTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::Implication);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Implication);
}

TEST(ImplTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
  EXPECT_FALSE(f.isAssociative());
}

TEST(ImplTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "~a | b");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(ImplTests, exprTest) {
  EXPECT_EQ(implExpr(Boolean(true), Boolean(false))->toString(), "~True | False");
}

TEST(ImplTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Impl, "Impl"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Impl, "Impl"));
}
