#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/comparison/Eqv.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Eqv;
const F f;

TEST(EqvTests, toStringTest) {
  EXPECT_EQ(f.toString(), "=");
}

TEST(EqvTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IComparable::getTypeStatic(), IComparable::getTypeStatic()));
}

TEST(EqvTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), Boolean::getTypeStatic());
}

TEST(EqvTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(EqvTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(EqvTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::Comparison);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Comparison);
}

TEST(EqvTests, isAssociativeTest) {
  EXPECT_TRUE(F::isAssociativeStatic());
  EXPECT_TRUE(f.isAssociative());
}

TEST(EqvTests, callTest) {
  EXPECT_EQ(f(Integer(5), Integer(3))->toString(), "False");
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "False");
  EXPECT_EQ(f(Integer(3), Integer(3))->toString(), "True");
  EXPECT_EQ(f(Integer(3), Rational(3, 1))->toString(), "True");
  EXPECT_EQ(f(Rational(5, 2), Integer(2))->toString(), "False");

  EXPECT_EQ(f(Complex(1, 1), Complex(1, 1))->toString(), "True");
  EXPECT_EQ(f(Complex(1, 1), Complex(1, 2))->toString(), "False");
  EXPECT_EQ(f(Complex(1, 1), Complex(2, 1))->toString(), "False");
  EXPECT_EQ(f(Complex(1, 1), Complex(2, 2))->toString(), "False");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "a - 3 = 0");
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "True");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(EqvTests, exprTest) {
  EXPECT_EQ(eqvExpr(Integer(10), Integer(10))->toString(), "10 = 10");
}

TEST(EqvTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Eqv, "Eqv"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Eqv, "Eqv"));
}
