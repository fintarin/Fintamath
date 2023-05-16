#include "gtest/gtest.h"

#include "fintamath/functions/comparison/Eqv.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Eqv f;

TEST(EqvTests, toStringTest) {
  EXPECT_EQ(f.toString(), "=");
}

TEST(EqvTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(EqvTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(EqvTests, callTest) {
  EXPECT_EQ(f(Integer(5), Integer(3))->toString(), "False");
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "False");
  EXPECT_EQ(f(Integer(3), Integer(3))->toString(), "True");
  EXPECT_EQ(f(Integer(3), Rational(3, 1))->toString(), "True");
  EXPECT_EQ(f(Rational(5, 2), Integer(2))->toString(), "False");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "a - 3 = 0");
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "True");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(EqvTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(EqvTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Eqv());
  EXPECT_EQ(Eqv(), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}
