#include "gtest/gtest.h"

#include "fintamath/functions/other/Factorial.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Factorial f;

TEST(FactorialTests, toStringTest) {
  EXPECT_EQ(f.toString(), "!");
}

TEST(FactorialTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(FactorialTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(FactorialTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(), "3628800");

  EXPECT_EQ(f(Variable("a"))->toString(), "a!");

  EXPECT_THROW(f(Integer(-10)), UndefinedUnaryOperatorException);
  EXPECT_THROW(f(Rational(1, 10)), UndefinedUnaryOperatorException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(FactorialTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(FactorialTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Factorial());
  EXPECT_EQ(Factorial(), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}
