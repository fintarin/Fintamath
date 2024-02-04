#include "gtest/gtest.h"

#include "fintamath/functions/powers/Sqr.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sqr f;

TEST(SqrTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sqr");
}

TEST(SqrTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SqrTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(100))->toString(), "10000");
  EXPECT_EQ(f(Integer(-100))->toString(), "10000");

  EXPECT_EQ(f(Rational(3, 5))->toString(), "9/25");

  EXPECT_EQ(f(Real("144.23"))->toString(), "20802.2929");

  EXPECT_EQ(f(Variable("a"))->toString(), "a^2");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SqrTests, exprTest) {
  EXPECT_EQ(sqrExpr(Integer(10))->toString(), "10^2");
}

TEST(SqrTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SqrTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sqr());
  EXPECT_EQ(Sqr(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sqr()));
  EXPECT_EQ(cast<IMathObject>(Sqr()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SqrTests, getTypeTest) {
  EXPECT_EQ(Sqr::getTypeStatic(), MathObjectType::Sqr);
  EXPECT_EQ(Sqr().getType(), MathObjectType::Sqr);
}
