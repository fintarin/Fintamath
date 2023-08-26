#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Min.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Max.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Min f;

TEST(MinTests, toStringTest) {
  EXPECT_EQ(f.toString(), "min");
}

TEST(MinTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Any);
}

TEST(MinTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1))->toString(), "-1");
  EXPECT_EQ(f(Integer(1), Integer(-1), Rational(-5, 2))->toString(), "-5/2");
  EXPECT_EQ(f(Integer(1), Rational(5, 2), Rational(-5, 2), Integer(-1))->toString(), "-5/2");

  EXPECT_EQ(f(Rational(-1), Variable("x"), Variable("y"), Integer(1))->toString(), "min(x, y, -1)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer(), Integer()), InvalidInputFunctionException);
}

TEST(MinTests, exprTest) {
  EXPECT_EQ(minExpr(Variable("a"), Variable("a"))->toString(), "min(a, a)");
}

TEST(MinTests, doArgsMatchTest) {
  EXPECT_FALSE(f.doArgsMatch({}));
}

TEST(MinTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Min());
  EXPECT_EQ(Min(), f);
  EXPECT_EQ(f, cast<IMathObject>(Min()));
  EXPECT_EQ(cast<IMathObject>(Min()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
  EXPECT_NE(f, Max());
  EXPECT_NE(Max(), f);
}

TEST(MinTests, getTypeIdTest) {
  EXPECT_EQ(Min::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Min));
  EXPECT_EQ(Min().getTypeId(), MathObjectTypeId(MathObjectType::Min));
}
