#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Equiv.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Equiv f;

TEST(EquivTests, toStringTest) {
  EXPECT_EQ(f.toString(), "<->");
}

TEST(EquivTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic(), Boolean::getClassStatic()));
}

TEST(EquivTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(EquivTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(EquivTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(EquivTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Equivalence);
}

TEST(EquivTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(EquivTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "(~a & ~b) | (a & b)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(EquivTests, exprTest) {
  EXPECT_EQ(equivExpr(Boolean(true), Boolean(false))->toString(), "(True & False) | (~True & ~False)");
}

TEST(EquivTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Equiv");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
