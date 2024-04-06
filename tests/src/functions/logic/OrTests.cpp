#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Or.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

const Or f;

TEST(OrTests, toStringTest) {
  EXPECT_EQ(f.toString(), "or");
}

TEST(OrTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(Boolean::getClassStatic()));
}

TEST(OrTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), Boolean::getClassStatic());
}

TEST(OrTests, isVariadicTest) {
  EXPECT_TRUE(f.isVariadic());
}

TEST(OrTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(OrTests, callTest) {
  EXPECT_EQ(f(Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(false), Boolean(false), Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true), Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false), Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true), Boolean(true), Boolean(true))->toString(), "True");

  EXPECT_EQ(f(Variable("a"))->toString(), "a");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "a | b");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Variable("c"))->toString(), "a | b | c");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Variable("a"), Variable("c"))->toString(), "a | b | c");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Variable("b"), Variable("a"))->toString(), "a | b");
  EXPECT_EQ(f(Variable("a"), Variable("b"), Boolean("True"), Variable("c"))->toString(), "True");
  EXPECT_EQ(f(Boolean("False"), Variable("a"), Variable("b"), Variable("c"))->toString(), "a | b | c");

  EXPECT_THROW(f(), InvalidInputFunctionException);
}

TEST(OrTests, exprTest) {
  EXPECT_EQ(orExpr(Boolean(true), Boolean(false))->toString(), "True | False");
}

TEST(OrTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Or"));
  EXPECT_EQ(f.getClass().getParent(), IFunction::getClassStatic());
}
