#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Deg.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Deg f;

TEST(DegTests, toStringTest) {
  EXPECT_EQ(f.toString(), "deg");
}

TEST(DegTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(DegTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(DegTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(DegTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(DegTests, getPriorityTest) {
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PostfixUnary);
}

TEST(DegTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(DegTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(), "Pi/180");
  EXPECT_EQ(f(Integer(10))->toString(), "Pi/18");
  EXPECT_EQ(f(Integer(-10))->toString(), "-Pi/18");
  EXPECT_EQ(f(Rational(1, 10))->toString(), "Pi/1800");

  EXPECT_EQ(f(Variable("a"))->toString(), "(Pi a)/180");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(DegTests, degTest) {
  EXPECT_EQ(degExpr(Integer(10))->toString(), "10 Pi/180");
}

TEST(DegTests, getClassTest) {
  EXPECT_EQ(f.getClass(), MathObjectClass("Deg"));
  EXPECT_EQ(f.getClass().getParent(), IOperator::getClassStatic());
}
