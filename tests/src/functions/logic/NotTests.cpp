#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Not.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Not f;

TEST(NotTests, toStringTest) {
  EXPECT_EQ(f.toString(), "~");
}

TEST(NotTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic()));
}

TEST(NotTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(NotTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(NotTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(NotTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PrefixUnary);
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

TEST(NotTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Not");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
