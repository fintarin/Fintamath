#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Add;
const F f;

TEST(AddTests, toStringTest) {
  EXPECT_EQ(f.toString(), "+");
}

TEST(AddTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(IArithmetic::getTypeStatic(), IArithmetic::getTypeStatic()));
}

TEST(AddTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), IArithmetic::getTypeStatic());
}

TEST(AddTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(AddTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AddTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Addition);
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
  EXPECT_EQ(F::getTypeStatic(), MathObjectType::Add);
  EXPECT_EQ(f.getType(), MathObjectType::Add);
}
