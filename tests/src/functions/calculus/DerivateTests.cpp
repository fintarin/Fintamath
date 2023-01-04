#include "gtest/gtest.h"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(DerivativeTests, toStringTest) {
  EXPECT_EQ(Derivative().toString(), "'");
}

TEST(DerivativeTests, getFunctionTypeTest) {
  EXPECT_EQ(Derivative().getFunctionType(), IFunction::Type::Unary);
}

TEST(DerivativeTests, getOperatorPriorityTest) {
  EXPECT_EQ(Derivative().getOperatorPriority(), IOperator::Priority::PostfixUnary);
}

TEST(DerivativeTests, callTest) {
  EXPECT_EQ(Derivative()(Variable("a"))->toString(), "1");
  EXPECT_EQ(Derivative()(Expression("a+a"))->toString(), "(2*a)'");
  EXPECT_EQ(Derivative()(Integer(5))->toString(), "0");

  std::unique_ptr<IFunction> f = std::make_unique<Derivative>();
  EXPECT_EQ((*f)(Integer(5))->toString(), "0");
  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
