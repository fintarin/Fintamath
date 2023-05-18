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

TEST(MulTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(MulTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Mul());
  EXPECT_EQ(Mul(), f);
  EXPECT_EQ(f, cast<IMathObject>(Mul()));
  EXPECT_EQ(cast<IMathObject>(Mul()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(MulTests, getTypeIdTest) {
  EXPECT_EQ(Mul::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Mul));
  EXPECT_EQ(Mul().getTypeId(), MathObjectTypeId(MathObjectType::Mul));
}
