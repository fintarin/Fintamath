#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Min.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/calculus/Max.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
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

  EXPECT_EQ(f(Integer(1), Rational(5, 2), Complex(1, 1))->toString(), "min(1, 5/2, 1 + I)");
  EXPECT_EQ(f(Integer(1), Complex(1, 1), Rational(5, 2))->toString(), "min(1, 1 + I, 5/2)");

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

TEST(MinTests, getTypeTest) {
  EXPECT_EQ(Min::getTypeStatic(), MathObjectType::Min);
  EXPECT_EQ(Min().getType(), MathObjectType::Min);
}
