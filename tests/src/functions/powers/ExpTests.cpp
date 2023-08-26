#include "gtest/gtest.h"

#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Exp f;

TEST(ExpTests, toStringTest) {
  EXPECT_EQ(f.toString(), "exp");
}

TEST(ExpTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(ExpTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "E^3");
  EXPECT_EQ(f(Integer(-3))->toString(), "1/(E^3)");
  EXPECT_EQ(f(Rational(1, 3))->toString(), "root(E, 3)");

  EXPECT_EQ(f(Variable("a"))->toString(), "E^a");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(ExpTests, exprTest) {
  EXPECT_EQ(expExpr(Integer(10))->toString(), "E^10");
}

TEST(ExpTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(ExpTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Exp());
  EXPECT_EQ(Exp(), f);
  EXPECT_EQ(f, cast<IMathObject>(Exp()));
  EXPECT_EQ(cast<IMathObject>(Exp()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(ExpTests, getTypeIdTest) {
  EXPECT_EQ(Exp::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Exp));
  EXPECT_EQ(Exp().getTypeId(), MathObjectTypeId(MathObjectType::Exp));
}
