#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Derivative.hpp"

#include "fintamath/exceptions/UndefinedUnaryOperatorException.hpp"
#include "fintamath/expressions/Expression.hpp"
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
  EXPECT_EQ(f(Variable("a"),Variable("a"))->toString(), "1");
  EXPECT_EQ(f(Variable("a"),Variable("b"))->toString(), "derivative(a, b)");
  EXPECT_EQ(f(Expression("a+a"),Variable("a"))->toString(), "derivative(2 a, a)");
  EXPECT_EQ(f(Integer(5),Variable("a"))->toString(), "0");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
