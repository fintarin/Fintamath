#include "gtest/gtest.h"

#include "fintamath/functions/other/Deg.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Deg f;

TEST(DegTests, toStringTest) {
  EXPECT_EQ(f.toString(), "deg");
}

TEST(DegTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(DegTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PostfixUnary);
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
  EXPECT_EQ(degExpr(Integer(10))->toString(), "10*1/180 Pi");
}

TEST(DegTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(DegTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Deg());
  EXPECT_EQ(Deg(), f);
  EXPECT_EQ(f, cast<IMathObject>(Deg()));
  EXPECT_EQ(cast<IMathObject>(Deg()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(DegTests, getTypeIdTest) {
  EXPECT_EQ(Deg::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Deg));
  EXPECT_EQ(Deg().getTypeId(), MathObjectTypeId(MathObjectType::Deg));
}
