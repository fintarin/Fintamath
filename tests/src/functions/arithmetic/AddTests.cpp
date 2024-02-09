#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Add f;

TEST(AddTests, toStringTest) {
  EXPECT_EQ(f.toString(), "+");
}

TEST(AddTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(AddTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Addition);
}

TEST(AddTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(AddTests, callTest) {
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "8");
  EXPECT_EQ(f(Integer(3), Rational(5, 2))->toString(), "11/2");
  EXPECT_EQ(f(Rational(5, 2), Integer(3))->toString(), "11/2");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 2))->toString(), "5");
  EXPECT_EQ(f(Rational(5, 2), Rational(5, 3))->toString(), "25/6");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "a + 3");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(AddTests, exprTest) {
  EXPECT_EQ(addExpr(Integer(10), Integer(10))->toString(), "10 + 10");
}

TEST(AddTests, getTypeTest) {
  EXPECT_EQ(Add::getTypeStatic(), MathObjectType::Add);
  EXPECT_EQ(Add().getType(), MathObjectType::Add);
}
