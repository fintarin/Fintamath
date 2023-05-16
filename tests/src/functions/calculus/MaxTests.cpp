#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Max.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Min.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Max f;

TEST(MaxTests, toStringTest) {
  EXPECT_EQ(f.toString(), "max");
}

TEST(MaxTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Any);
}

TEST(MaxTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Integer(-1), Rational(-5, 2))->toString(), "1");
  EXPECT_EQ(f(Integer(1), Rational(5, 2), Rational(-5, 2), Integer(-1))->toString(), "5/2");

  EXPECT_EQ(f(Rational(-1), Variable("x"), Variable("y"), Integer(1))->toString(), "max(x, y, 1)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Integer(), Boolean()), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(), Boolean(), Integer()), InvalidInputFunctionException);
  EXPECT_THROW(f(Boolean(), Integer(), Integer()), InvalidInputFunctionException);
}

TEST(MaxTests, doArgsMatchTest) {
  EXPECT_FALSE(f.doArgsMatch({}));
}

TEST(MaxTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Max());
  EXPECT_EQ(Max(), f);
  EXPECT_EQ(f, cast<IMathObject>(Max()));
  EXPECT_EQ(cast<IMathObject>(Max()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
  EXPECT_NE(f, Min());
  EXPECT_NE(Min(), f);
}
