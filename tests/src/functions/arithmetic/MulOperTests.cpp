#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/MulOper.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const MulOper f;

TEST(MulOperTests, toStringTest) {
  EXPECT_EQ(f.toString(), "*");
}

TEST(MulOperTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic(), IArithmetic::getClassStatic()));
}

TEST(MulOperTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(MulOperTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(MulOperTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(MulOperTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Multiplication);
}

TEST(MulOperTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(MulOperTests, callTest) {
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

TEST(MulOperTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "MulOper");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
