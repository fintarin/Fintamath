#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Mul f;

TEST(MulTests, toStringTest) {
  EXPECT_EQ(f.toString(), "*");
}

TEST(MulTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(MulTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Multiplication);
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
  EXPECT_EQ(Mul::getTypeStatic(), MathObjectType::Mul);
  EXPECT_EQ(Mul().getType(), MathObjectType::Mul);
}
