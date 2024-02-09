#include "gtest/gtest.h"

#include "fintamath/functions/comparison/Neqv.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Neqv f;

TEST(NeqvTests, toStringTest) {
  EXPECT_EQ(f.toString(), "!=");
}

TEST(NeqvTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(NeqvTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(NeqvTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(NeqvTests, callTest) {
  EXPECT_EQ(f(Integer(5), Integer(3))->toString(), "True");
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "True");
  EXPECT_EQ(f(Integer(3), Integer(3))->toString(), "False");
  EXPECT_EQ(f(Integer(3), Rational(3, 1))->toString(), "False");
  EXPECT_EQ(f(Rational(5, 2), Integer(2))->toString(), "True");

  EXPECT_EQ(f(Complex(1, 1), Complex(1, 1))->toString(), "False");
  EXPECT_EQ(f(Complex(1, 1), Complex(1, 2))->toString(), "True");
  EXPECT_EQ(f(Complex(1, 1), Complex(2, 1))->toString(), "True");
  EXPECT_EQ(f(Complex(1, 1), Complex(2, 2))->toString(), "True");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "a - 3 != 0");
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "False");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(NeqvTests, exprTest) {
  EXPECT_EQ(neqvExpr(Integer(10), Integer(10))->toString(), "10 != 10");
}

TEST(NeqvTests, getTypeTest) {
  EXPECT_EQ(Neqv::getTypeStatic(), MathObjectType::Neqv);
  EXPECT_EQ(Neqv().getType(), MathObjectType::Neqv);
}
