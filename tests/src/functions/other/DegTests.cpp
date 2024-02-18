#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/other/Deg.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

using F = Deg;
const F f;

TEST(DegTests, toStringTest) {
  EXPECT_EQ(f.toString(), "deg");
}

TEST(DegTests, getArgumentTypesTest) {
  EXPECT_THAT(f.getArgumentTypes(), testing::ElementsAre(INumber::getTypeStatic()));
}

TEST(DegTests, getReturnTypeTest) {
  EXPECT_EQ(f.getReturnType(), INumber::getTypeStatic());
}

TEST(DegTests, isVariadicTest) {
  EXPECT_FALSE(F::isVariadicStatic());
  EXPECT_FALSE(f.isVariadic());
}

TEST(DegTests, isEvaluatableTest) {
  EXPECT_TRUE(F::isEvaluatableStatic());
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(DegTests, getPriorityTest) {
  EXPECT_EQ(F::getPriorityStatic(), IOperator::Priority::PostfixUnary);
  EXPECT_EQ(f.getPriority(), IOperator::Priority::PostfixUnary);
}

TEST(DegTests, isAssociativeTest) {
  EXPECT_FALSE(F::isAssociativeStatic());
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

TEST(DegTests, getTypeTest) {
  EXPECT_EQ(F::getTypeStatic(), MathObjectType(MathObjectType::Deg, "Deg"));
  EXPECT_EQ(f.getType(), MathObjectType(MathObjectType::Deg, "Deg"));
}
