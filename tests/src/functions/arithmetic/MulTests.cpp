#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Mul;
const F f;

TEST(MulTests, toStringTest) {
  EXPECT_EQ(f.toString(), "*");
}

TEST(MulTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IArithmetic::getTypeStatic(), IArithmetic::getTypeStatic()));
}

TEST(MulTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IArithmetic::getTypeStatic());
}

TEST(MulTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(MulTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(MulTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Multiplication);
}

TEST(MulTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(MulTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "15");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "15/2");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "15/2");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "25/6");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3 a");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(MulTests, exprTest) {
  EXPECT_EQ(mulExpr(Integer(10), Integer(10))->toString(), "10*10");
}

TEST(MulTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Mul);
  EXPECT_EQ(f.getType(), MathObjectType::Mul);
}
