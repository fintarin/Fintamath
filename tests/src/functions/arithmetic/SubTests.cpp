#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Sub.hpp"

#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Sub f;

TEST(SubTests, toStringTest) {
  EXPECT_EQ(f.toString(), "-");
}

TEST(SubTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(SubTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Addition);
}

TEST(SubTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(SubTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "-2");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "1/2");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "-1/2");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 2))->toString(), "0");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "5/6");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "-a + 3");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SubTests, exprTest) {
  EXPECT_EQ(subExpr(Integer(10), Integer(10))->toString(), "10 - 10");
}

TEST(SubTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SubTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sub());
  EXPECT_EQ(Sub(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sub()));
  EXPECT_EQ(cast<IMathObject>(Sub()), f);
  EXPECT_NE(f, Mul());
  EXPECT_NE(Mul(), f);
  EXPECT_NE(f, Neg());
  EXPECT_NE(Neg(), f);
}

TEST(SubTests, getTypeTest) {
  EXPECT_EQ(Sub::getTypeStatic(), MathObjectType::Sub);
  EXPECT_EQ(Sub().getType(), MathObjectType::Sub);
}
