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

TEST(CommaTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IMathObject::getTypeStatic(), IMathObject::getTypeStatic()));
}

TEST(CommaTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IMathObject::getTypeStatic());
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
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Comma);
}

TEST(CommaTests, isAssociativeTest) {
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

TEST(CommaTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Comma);
  EXPECT_EQ(f.getType(), MathObjectType::Comma);
}
