#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Derivative.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Derivative f;

TEST(DerivativeTests, toStringTest) {
  EXPECT_EQ(f.toString(), "derivative");
}

TEST(DerivativeTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(DerivativeTests, callTest) {
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "1");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "derivative(a, b)");
  EXPECT_EQ(f(Expression("a+a"), Variable("a"))->toString(), "derivative(2 a, a)"); // TODO: derivative
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "0");

  EXPECT_THROW(f(Integer(5), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Expression("a+a")), InvalidInputException); // TODO: derivative

  EXPECT_THROW(f(), InvalidInputException);
  EXPECT_THROW(f(Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputException);
}

TEST(DerivativeTests, exprTest) {
  EXPECT_EQ(derivativeExpr(Variable("a"), Variable("a"))->toString(), "derivative(a, a)");
}

TEST(DerivativeTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(DerivativeTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Derivative());
  EXPECT_EQ(Derivative(), f);
  EXPECT_EQ(f, cast<IMathObject>(Derivative()));
  EXPECT_EQ(cast<IMathObject>(Derivative()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(DerivativeTests, getTypeIdTest) {
  EXPECT_EQ(Derivative::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Derivative));
  EXPECT_EQ(Derivative().getTypeId(), MathObjectTypeId(MathObjectType::Derivative));
}
