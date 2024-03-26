#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = UnaryPlus;
const F f;

TEST(UnaryPlusTests, toStringTest) {
  EXPECT_EQ(f.toString(), "+");
}

TEST(UnaryPlusTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
}

TEST(UnaryPlusTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IArithmetic::getClassStatic());
}

TEST(UnaryPlusTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(UnaryPlusTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(UnaryPlusTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::PrefixUnary);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PrefixUnary);
}

TEST(UnaryPlusTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
  EXPECT_FALSE(f.isAssociative());
}

TEST(UnaryPlusTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "3");
  EXPECT_EQ(f(Rational(5, 2))->toString(), "5/2");
  EXPECT_EQ(f(Rational(-5, 2))->toString(), "-5/2");

  EXPECT_EQ(f(Variable("a"))->toString(), "a");

  EXPECT_THROW(f(Integer(1), Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(UnaryPlusTests, getClassTest) {
  EXPECT_EQ(F::getClassStatic(), MathObjectClass("UnaryPlus"));
  EXPECT_EQ(F::getClassStatic().getParent(), IOperator::getClassStatic());
}
