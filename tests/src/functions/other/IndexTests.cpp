#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Index.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

using F = Index;
const F f;

TEST(IndexTests, toStringTest) {
  EXPECT_EQ(f.toString(), "_");
}

TEST(IndexTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(Variable::getTypeStatic(), Integer::getTypeStatic()));
}

TEST(IndexTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), Variable::getTypeStatic());
}

TEST(IndexTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(IndexTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(IndexTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::Exponentiation);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Exponentiation);
}

TEST(IndexTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
  EXPECT_FALSE(f.isAssociative());
}

TEST(IndexTests, callTest) {
  EXPECT_EQ(f(Expression("a"), Integer(0))->toString(), "a_0");
  EXPECT_EQ(f(Variable("a"), Integer(1))->toString(), "a_1");
  EXPECT_EQ(f(Variable("a"), Integer(2))->toString(), "a_2");
  EXPECT_EQ(f(Variable("a"), Integer("100000000000000000000000000000000"))->toString(),
            "a_100000000000000000000000000000000");

  EXPECT_THROW(f(Variable("a"), Variable("a"))->toString(), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Expression("a+1"))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("a"), Integer(-1))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("1"), Integer(2))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("a+1"), Integer(2))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("a+1"), Expression("a+1"))->toString(), InvalidInputException);
  EXPECT_THROW(f(Expression("a"), Expression("a>1"))->toString(), InvalidInputException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(IndexTests, exprTest) {
  EXPECT_EQ(indexExpr(Variable("a"), Integer(1))->toString(), "a_1");
}

TEST(IndexTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Index, "Index"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Index, "Index"));
}
