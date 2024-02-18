#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Neg.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Neg;
const F f;

TEST(NegTests, toStringTest) {
  EXPECT_EQ(f.toString(), "-");
}

TEST(NegTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IArithmetic::getTypeStatic()));
}

TEST(NegTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IArithmetic::getTypeStatic());
}

TEST(NegTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(NegTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(NegTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::PrefixUnary);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PrefixUnary);
}

TEST(NegTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
  EXPECT_FALSE(f.isAssociative());
}

TEST(NegTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "-3");
  EXPECT_EQ(f(Rational(5, 2))->toString(), "-5/2");
  EXPECT_EQ(f(Rational(-5, 2))->toString(), "5/2");

  EXPECT_EQ(f(Variable("a"))->toString(), "-a");

  EXPECT_THROW(f(Integer(1), Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(NegTests, exprTest) {
  EXPECT_EQ(negExpr(Integer(10))->toString(), "-10");
}

TEST(NegTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Neg, "Neg"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Neg, "Neg"));
}
