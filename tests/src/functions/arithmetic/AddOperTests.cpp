#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/AddOper.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const AddOper f;

TEST(AddOperTests, toStringTest) {
  EXPECT_EQ(f.toString(), "+");
}

TEST(AddOperTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic(), IArithmetic::getClassStatic()));
}

TEST(AddOperTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(AddOperTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(AddOperTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(AddOperTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::Addition);
}

TEST(AddOperTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(AddOperTests, callTest) {
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

TEST(AddOperTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "AddOper");
  EXPECT_EQ(f.getClass()->getParent(), IOperator::getClassStatic());
}
