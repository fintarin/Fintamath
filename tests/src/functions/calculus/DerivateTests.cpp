#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Derivative.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Derivative f;

TEST(DerivativeTests, toStringTest) {
  EXPECT_EQ(f.toString(), "'");
}

TEST(DerivativeTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(DerivativeTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(DerivativeTests, callTest) {
  EXPECT_EQ(f(Variable("a"))->toString(), "1");
  EXPECT_EQ(f(Expression("a+a"))->toString(), "(2*a)'");
  EXPECT_EQ(f(Integer(5))->toString(), "0");

  EXPECT_EQ(f(Integer(5))->toString(), "0");
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
