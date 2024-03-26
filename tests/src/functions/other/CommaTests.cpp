#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Comma.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

using F = Comma;
const F f;

TEST(CommaTests, toStringTest) {
  EXPECT_EQ(f.toString(), ",");
}

TEST(CommaTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IMathObject::getClassStatic(), IMathObject::getClassStatic()));
}

TEST(CommaTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IMathObject::getClassStatic());
}

TEST(CommaTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(CommaTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CommaTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::Comma);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Comma);
}

TEST(CommaTests, isAssociativeTest) {
  EXPECT_TRUE(F::isAssociativeStatic());
  EXPECT_TRUE(f.isAssociative());
}

TEST(CommaTests, callTest) {
  EXPECT_THROW(f(Variable("a"), Variable("a"))->toString(), InvalidInputException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CommaTests, exprTest) {
  EXPECT_EQ(commaExpr(Variable("a"), Integer(1))->toString(), "a , 1");
}

TEST(CommaTests, getClassTest) {
  EXPECT_EQ(F::getClassStatic(), MathObjectClass("Comma"));
  EXPECT_EQ(F::getClassStatic().getParent(), IOperator::getClassStatic());
}
