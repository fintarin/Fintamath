#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/logic/Nequiv.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

using F = Nequiv;
const F f;

TEST(NequivTests, toStringTest) {
  EXPECT_EQ(f.toString(), "!<->");
}

TEST(NequivTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(Boolean::getTypeStatic(), Boolean::getTypeStatic()));
}

TEST(NequivTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), Boolean::getTypeStatic());
}

TEST(NequivTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(NequivTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(NequivTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Equivalence);
}

TEST(NequivTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(NequivTests, callTest) {
  EXPECT_EQ(f(Boolean(false), Boolean(false))->toString(), "False");
  EXPECT_EQ(f(Boolean(false), Boolean(true))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(false))->toString(), "True");
  EXPECT_EQ(f(Boolean(true), Boolean(true))->toString(), "False");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "(a & ~b) | (~a & b)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true)), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(true), Boolean(true), Boolean(true)), InvalidInputFunctionException);
}

TEST(NequivTests, exprTest) {
  EXPECT_EQ(nequivExpr(Boolean(true), Boolean(false))->toString(), "(~True & False) | (True & ~False)");
}

TEST(NequivTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Nequiv);
  EXPECT_EQ(f.getType(), MathObjectType::Nequiv);
}
