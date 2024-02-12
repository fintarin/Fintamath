#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Div;
const F f;

TEST(DivTests, toStringTest) {
  EXPECT_EQ(f.toString(), "/");
}

TEST(DivTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IArithmetic::getTypeStatic(), IArithmetic::getTypeStatic()));
}

TEST(DivTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IArithmetic::getTypeStatic());
}

TEST(DivTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(DivTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(DivTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::Multiplication);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Multiplication);
}

TEST(DivTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
  EXPECT_FALSE(f.isAssociative());
}

TEST(DivTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "3/5");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "6/5");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "5/6");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "3/2");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "3/a");

  EXPECT_EQ(f(Integer(1), Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(0), Integer(0))->toString(), "Undefined");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(DivTests, exprTest) {
  EXPECT_EQ(divExpr(Integer(10), Integer(10))->toString(), "10/10");
}

TEST(DivTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Div);
  EXPECT_EQ(f.getType(), MathObjectType::Div);
}
